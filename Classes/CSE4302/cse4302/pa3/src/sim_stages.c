/**
 * University of Connecticut
 * CSE 4302: Computer Architecture
 * Fall 2025
 * 
 * Programming Assignment 3: MultiCycle Stall + Out Of Order + Seperate Execution Units
 * 
 * riscy-uconn: sim_stages.c
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction_map.h"
#include "sim_core.h"
#include "sim_stages.h"
#include "decode_fields.h"

/**
 * Debug flags
 */
int debug = 0;           /* Set to 1 for additional debugging information. */
int pipe_trace = 1;      /* Set to 1 for pipe trace. */
int pipe_trace_mode = 3; 

static void prepare_decode_inst(struct State *inst,
                                unsigned int rs1_val,
                                unsigned int rs2_val)
{
    if (!inst->valid) return;

    uint32_t opcode = inst->opcode;

    inst->alu_in1 = rs1_val;
    inst->alu_in2 = rs2_val;

    switch (opcode) {
        case RTYPE:
            break;

        case ITYPE_ARITH:
            inst->alu_in2 = (uint32_t)inst->imm;
            if (inst->imm & 0x800)
                inst->imm |= 0xFFFFF000;
            break;

        case ITYPE_LOAD:
            inst->alu_in2 = (uint32_t)inst->imm;
            break;

        case STYPE:
            inst->alu_in2    = (uint32_t)inst->imm;
            inst->mem_buffer = rs2_val;
            break;

        case BTYPE:
            inst->br_addr =
                inst->inst_addr + (uint32_t)inst->imm;
            break;

        case JAL:
            inst->link_addr = inst->inst_addr + 4u;
            inst->br_addr   = inst->inst_addr +
                              (uint32_t)inst->imm;
            j_taken = 1;
            advance_pc(inst->br_addr);
            break;

        case JALR: {
            inst->alu_in2 = (uint32_t)inst->imm;
            unsigned int target =
                (inst->alu_in1 + inst->alu_in2) & ~1u;
            inst->link_addr = inst->inst_addr + 4u;
            inst->br_addr   = target;
            j_taken = 1;
            advance_pc(inst->br_addr);
            break;
        }

        case LUI:
            inst->alu_in1 = 0u;
            inst->alu_in2 =
                (uint32_t)(inst->inst & bit_31_downto_12);
            inst->imm =
                (inst->inst & bit_31_downto_12);
            break;

        default:
            break;
    }
}


/**
 * Fetch stage implementation.
 */
struct State fetch() {
    
    /*Insert your code here*/
    fetch_out_n = nop;

    // Freeze if pipe_stall
    if (pipe_stall) {
        fetch_out_n = fetch_out;
        return fetch_out_n;
    }

    // Flush if j taken or branch mispredicted
    if (j_taken || br_mispredicted) {
        j_taken = 0;
        br_mispredicted = 0;
        return fetch_out_n;
    }

    fetch_out_n.inst_addr = pc;
    fetch_out_n.inst = memory[pc / 4];
    fetch_out_n.valid = 1;
    advance_pc(pc + 4);
    
    return fetch_out_n;
}

/**
 * Decode stage implementation
 */
struct State decode() {

    decode_out_n = fetch_out;
    pipe_stall = 0;

    // If branch was just resolved taken or JAL/JALR redirected PC,
    // kill this stage this cycle (same as PA2)
    if (br_mispredicted) {
        decode_out_n = nop;
        return decode_out_n;
    }

    // If fetch_out is nop / invalid, just return it
    if (!decode_out_n.valid) {
        return decode_out_n;
    }

    
    // Parse instruction fields into decode_out_n.{opcode,rs1,rs2,rd,imm,...}
    decode_fields(&decode_out_n);

    int opcode = decode_out_n.opcode;
    int rs1 = decode_out_n.rs1;
    int rs2 = decode_out_n.rs2;
    int rd  = decode_out_n.rd;

    // Figure out which operands are actually needed
    int need_rs1 =
        (opcode == RTYPE)      ||
        (opcode == ITYPE_ARITH)||
        (opcode == ITYPE_LOAD) ||
        (opcode == STYPE)      ||
        (opcode == BTYPE)      ||
        (opcode == JALR);

    int need_rs2 =
        (opcode == RTYPE) ||
        (opcode == STYPE) ||
        (opcode == BTYPE);

    // Read regfile values
    unsigned int rs1_val = need_rs1 ? (uint32_t)registers[rs1] : 0u;
    unsigned int rs2_val = need_rs2 ? (uint32_t)registers[rs2] : 0u;

    // check dependencies
    int dep_ex_rs1     = we_exe     && rs1 != 0 && (ws_exe     == rs1);
    int dep_ex_rs2     = we_exe     && rs2 != 0 && (ws_exe     == rs2);
    int dep_wb_rs1     = we_wb      && rs1 != 0 && (ws_wb      == rs1);
    int dep_wb_rs2     = we_wb      && rs2 != 0 && (ws_wb      == rs2);
    int dep_ldwb_rs1   = we_ld_wb   && rs1 != 0 && (ws_ld_wb   == rs1);
    int dep_ldwb_rs2   = we_ld_wb   && rs2 != 0 && (ws_ld_wb   == rs2);
    int dep_mem_rs1    = we_mem     && rs1 != 0 && (ws_mem     == rs1);
    int dep_mem_rs2    = we_mem     && rs2 != 0 && (ws_mem     == rs2);

    // Forwarding
    if (forwarding_enabled) {
        if (need_rs1) {
            if (dep_ex_rs1)        rs1_val = (uint32_t)dout_exe;
            else if (dep_wb_rs1)   rs1_val = (uint32_t)dout_wb;
            else if (dep_ldwb_rs1) rs1_val = (uint32_t)dout_ld_wb;
            else if (dep_mem_rs1 && !dmem_busy) rs1_val = (uint32_t)dout_mem;
        }
        if (need_rs2) {
            if (dep_ex_rs2)        rs2_val = (uint32_t)dout_exe;
            else if (dep_wb_rs2)   rs2_val = (uint32_t)dout_wb;
            else if (dep_ldwb_rs2) rs2_val = (uint32_t)dout_ld_wb;
            else if (dep_mem_rs2 && !dmem_busy) rs2_val = (uint32_t)dout_mem;
        }
    }

    
    int is_load      = (opcode == ITYPE_LOAD);
    int is_store     = (opcode == STYPE);
    int is_terminate = (opcode == ITYPE_ARITH &&
                        rd == 0 &&
                        rs1 == 0 &&
                        decode_out_n.imm == 1); // addi x0,x0,1

    int load_unit_busy      = dmem_busy;
    // load unit finishing on the last cycle
    int load_unit_finishing = dmem_busy &&
                              (dmem_cycles == dmem_access_cycles);

    // Information about the in-flight load in the dedicated load unit
    int load_dest_valid =
        load_unit_busy &&
        ld_out_n.valid &&
        (ld_out_n.opcode == ITYPE_LOAD) &&
        (ld_out_n.rd != 0);

    // RAW hazard: this decode instruction reads the destination of the in-flight load
    int load_raw_hazard_rs1 =
        load_dest_valid &&
        !load_unit_finishing &&
        need_rs1 &&
        (rs1 == ld_out_n.rd);

    int load_raw_hazard_rs2 =
        load_dest_valid &&
        !load_unit_finishing &&
        need_rs2 &&
        (rs2 == ld_out_n.rd);

    // WAW hazard between non-load/store in decode and a valid load in the load unit
    int waw_hazard =
        (!is_load && !is_store &&
         rd != 0 &&
         load_dest_valid &&
         (rd == ld_out_n.rd) &&
         !load_unit_finishing);

    // Case 1: OOO disabled (in-order pipeline)
    // Stall if load unit is busy with a multi-cycle load
    if (!ooo_enabled) {
        if (load_unit_busy && !load_unit_finishing) {
            pipe_stall = 1;
            decode_out_n = nop;
            return decode_out_n;
        }

        // When forwarding is disabled, stall on any RAW hazard with older in-flight instructions
        if (!forwarding_enabled) {
            int raw_hazard_rs1 =
                need_rs1 &&
                (dep_ex_rs1 || dep_wb_rs1 || dep_ldwb_rs1 || load_raw_hazard_rs1);
            int raw_hazard_rs2 =
                need_rs2 &&
                (dep_ex_rs2 || dep_wb_rs2 || dep_ldwb_rs2 || load_raw_hazard_rs2);

            if (raw_hazard_rs1 || raw_hazard_rs2) {
                pipe_stall = 1;
                decode_out_n = nop;
                return decode_out_n;
            }
        }
    }

    // Case 2: OOO enabled
    if (ooo_enabled) {

        int raw_hazard_rs1 = 0;
        int raw_hazard_rs2 = 0;

        // Always treat an in-flight load as a potential RAW hazard until its final cycle
        if (load_raw_hazard_rs1) raw_hazard_rs1 = 1;
        if (load_raw_hazard_rs2) raw_hazard_rs2 = 1;

        // If forwarding is disabled, also stall on RAW hazards with EX / WB results
        if (!forwarding_enabled) {
            if (need_rs1 && (dep_ex_rs1 || dep_wb_rs1 || dep_ldwb_rs1))
                raw_hazard_rs1 = 1;
            if (need_rs2 && (dep_ex_rs2 || dep_wb_rs2 || dep_ldwb_rs2))
                raw_hazard_rs2 = 1;
        }

        // When any instruction except terminate is in decode, it stalls if any operand has a RAW hazard
        if (!is_terminate && (raw_hazard_rs1 || raw_hazard_rs2)) {
            pipe_stall = 1;
            decode_out_n = nop;
            return decode_out_n;
        }

        // Terminate must wait for an older multi-cycle load to complete
        if (is_terminate) {
            if (load_unit_busy && !load_unit_finishing) {
                pipe_stall = 1;
                decode_out_n = nop;
                return decode_out_n;
            }
        }

        // When a non load/store instruction is in decode and there is a WAW hazard for a valid
        // instruction in the load stage, stall so the older load can commit first.
        if (waw_hazard) {
            pipe_stall = 1;
            decode_out_n = nop;
            return decode_out_n;
        }

        // When a load is in decode and there is a load active in the load unit (not completed),
        // stall due to structural hazard for the load unit.
        if (is_load) {
            if (load_unit_busy && !load_unit_finishing) {
                pipe_stall = 1;
                decode_out_n = nop;
                return decode_out_n;
            }
        }

        // When a store is in decode and there is a load active in the load unit (not completed),
        // stall to conservatively handle potential WAR hazards in memory.
        if (is_store) {
            if (load_unit_busy && !load_unit_finishing) {
                pipe_stall = 1;
                decode_out_n = nop;
                return decode_out_n;
            }
        }
    }


    // If we reach here, we are allowed to issue.
    // Fill the rest of the fields like PA2.
    decode_out_n.alu_in1 = rs1_val;
    decode_out_n.alu_in2 = rs2_val;

    switch (opcode) {
        case RTYPE:
            break;

        case ITYPE_ARITH:
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            if (decode_out_n.imm & 0x800)
                decode_out_n.imm |= 0xFFFFF000;
            break;

        case ITYPE_LOAD:
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            break;

        case STYPE:
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            decode_out_n.mem_buffer = rs2_val;
            break;

        case BTYPE:
            decode_out_n.br_addr =
                decode_out_n.inst_addr + (uint32_t)decode_out_n.imm;
            break;

        case JAL:
            decode_out_n.link_addr = decode_out_n.inst_addr + 4u;
            decode_out_n.br_addr   = decode_out_n.inst_addr +
                                     (uint32_t)decode_out_n.imm;
            j_taken = 1;
            advance_pc(decode_out_n.br_addr);
            break;

        case JALR: {
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            unsigned int target =
                (decode_out_n.alu_in1 + decode_out_n.alu_in2) & ~1u;
            decode_out_n.link_addr = decode_out_n.inst_addr + 4u;
            decode_out_n.br_addr   = target;
            j_taken = 1;
            advance_pc(decode_out_n.br_addr);
            break;
        }

        case LUI:
            decode_out_n.alu_in1 = 0u;
            decode_out_n.alu_in2 =
                (uint32_t)(decode_out_n.inst & bit_31_downto_12);
            decode_out_n.imm =
                (decode_out_n.inst & bit_31_downto_12);
            break;

        default:
            break;
    }

    return decode_out_n;
}



/**
 * Execute stage implementation
 */
struct State execute() {
    ex_out_n = decode_out;

    if (!ex_out_n.valid) {
        we_exe = 0;
        ws_exe = 0;
        dout_exe = 0;
        return ex_out_n;
    }

    ws_exe = 0;
    we_exe = 0;
    br_mispredicted = 0;

    unsigned int opcode = ex_out_n.opcode;
    unsigned int funct3 = ex_out_n.funct3;
    unsigned int funct7 = ex_out_n.funct7;

    unsigned int r1 = ex_out_n.alu_in1;
    unsigned int r2 = ex_out_n.alu_in2;

    switch (opcode) {
        case RTYPE: {
            switch (funct3) {
                case ADD_SUB:
                    ex_out_n.alu_out = (funct7 == SUB_F7) ? (r1 - r2) : (r1 + r2);
                    break;
                case AND: ex_out_n.alu_out = r1 & r2; break;
                case OR:  ex_out_n.alu_out = r1 | r2; break;
                case XOR: ex_out_n.alu_out = r1 ^ r2; break;
                case SLT: ex_out_n.alu_out = (r1 < r2) ? 1u : 0u; break;
                case SLL: ex_out_n.alu_out = r1 << (r2 & 0x1F); break;
                case SRL: {
                    unsigned int sh = (r2 & 0x1F);
                    if (funct7 == SUB_F7) {
                        // arithmetic right shift
                        ex_out_n.alu_out = (sh == 0)
                            ? r1
                            : ((r1 >> sh) |
                               ((r1 & 0x80000000u)
                                ? (~0u << (32 - sh))
                                : 0u));
                    } else {
                        // logical right shift
                        ex_out_n.alu_out = r1 >> sh;
                    }
                    break;
                }
                default:
                    ex_out_n.alu_out = 0;
                    break;
            }

            if (ex_out_n.rd != 0) {
                we_exe  = 1;
                ws_exe  = ex_out_n.rd;
                dout_exe = ex_out_n.alu_out;
            }
            break;
        }

        case ITYPE_ARITH: {
            unsigned int shamt = (r2 & 0x1F);
            switch (funct3) {
                case ADD_SUB: ex_out_n.alu_out = r1 + r2; break;
                case AND:     ex_out_n.alu_out = r1 & r2; break;
                case OR:      ex_out_n.alu_out = r1 | r2; break;
                case XOR:     ex_out_n.alu_out = r1 ^ r2; break;
                case SLT:     ex_out_n.alu_out = (r1 < r2) ? 1u : 0u; break;
                case SLL:     ex_out_n.alu_out = r1 << shamt; break;
                case SRL: {
                    // SRL / SRAI check high bits of r2 (same trick you had in PA2)
                    if (((r2 >> 5) & 0x7F) == SUB_F7) {
                        ex_out_n.alu_out = (shamt == 0)
                            ? r1
                            : ((r1 >> shamt) |
                               ((r1 & 0x80000000u)
                                ? (~0u << (32 - shamt))
                                : 0u));
                    } else {
                        ex_out_n.alu_out = r1 >> shamt;
                    }
                    break;
                }
                default:
                    ex_out_n.alu_out = 0;
                    break;
            }

            if (ex_out_n.rd != 0) {
                we_exe   = 1;
                ws_exe   = ex_out_n.rd;
                dout_exe = ex_out_n.alu_out;
            }
            break;
        }

        case BTYPE: {
            int br_taken = 0;
            unsigned int r1 = registers[ex_out_n.rs1];
            unsigned int r2 = registers[ex_out_n.rs2];

            switch (funct3) {
                case BEQ: br_taken = (r1 == r2); break;
                case BNE: br_taken = (r1 != r2); break;
                case BLT: {
                    unsigned int s1 = r1 ^ 0x80000000u;
                    unsigned int s2 = r2 ^ 0x80000000u;
                    br_taken = (s1 < s2);
                    break;
                }
                case BGE: {
                    unsigned int s1 = r1 ^ 0x80000000u;
                    unsigned int s2 = r2 ^ 0x80000000u;
                    br_taken = (s1 >= s2);
                    break;
                }
                default:
                    break;
            }

            if (br_taken) {
                ex_out_n.br_addr = ex_out_n.inst_addr + (unsigned int)ex_out_n.imm;
                advance_pc(ex_out_n.br_addr);
                br_mispredicted = 1;
            }
            break;
        }

        case JAL:
        case JALR:
            ex_out_n.alu_out = ex_out_n.link_addr;
            if (ex_out_n.rd != 0) {
                we_exe   = 1;
                ws_exe   = ex_out_n.rd;
                dout_exe = ex_out_n.alu_out;
            }
            break;

        case LUI:
            ex_out_n.alu_out = (uint32_t)ex_out_n.imm;
            if (ex_out_n.rd != 0) {
                we_exe   = 1;
                ws_exe   = ex_out_n.rd;
                dout_exe = ex_out_n.alu_out;
            }
            break;

        // No longer in execute
        case ITYPE_LOAD:
        case STYPE:
            ex_out_n = nop;
            break;

        default:
            break;
    }

    return ex_out_n;
}

/**
 * Implementation for Loads
 */
struct State load_stage() {
    ld_out_n = ld_out;
    wb_ld_out_n = nop;

    we_mem = 0;
    ws_mem = 0;
    dout_mem = 0;
    

    // During its last execution cycle, the busy flag is de-asserted and the load
    // from memory completes with data forwarded if forwarding is enabled. The above-mentioned stalls
    // apply when the load stage is busy. A load in its final execution cycle may not stall decode since it
    // is considered to have completed execution in this cycle. Do not make any assumptions about when
    // in the execution stage a load to memory is initiated and memory is being read. The only known
    // fact about the load stage is that a load completes in its final cycle of execution.

    // if not busy, insert load
    if (!dmem_busy && decode_out.valid && decode_out.opcode == ITYPE_LOAD) {
        ld_out_n = decode_out;
        unsigned int base = ld_out_n.alu_in1;
        unsigned int off  = ld_out_n.alu_in2;
        ld_out_n.mem_addr = base + off;

        // set as busy, reset cycles to 0 as new load has entered
        dmem_busy = 1;
        dmem_cycles = 0;

        // data not yet ready
        we_mem = 0;  
    } 

    // if busy, stall and increment cycles
    if (dmem_busy) {
        dmem_cycles++;

        // once at 6 cycles, complete load
        if (dmem_cycles >= dmem_access_cycles) {
            unsigned int addr = ld_out.mem_addr;
            ld_out_n.mem_buffer = memory[addr];
            wb_ld_out_n = ld_out_n;

            // forward data if enabled
            if (forwarding_enabled && ld_out_n.rd != 0) {
                we_mem = 1;
                ws_mem = ld_out_n.rd;
                dout_mem = ld_out_n.mem_buffer;
            }

            // clear for next load
            ld_out_n = nop;
            dmem_busy = 0;
            dmem_cycles = 0;
        } 

        return ld_out_n;
    }

    return ld_out_n;
}

/**
 * Implementation for Stores
 */
struct State store_stage() {
    st_out_n = nop;

    // If  store, execute 
    if (decode_out.valid && decode_out.opcode == STYPE) {
        st_out_n = decode_out;

        unsigned int base = st_out_n.alu_in1;        // rs1 value
        unsigned int off  = st_out_n.alu_in2;        // imm
        unsigned int addr = base + off;

        memory[addr] = st_out_n.mem_buffer;

    } 

    return st_out_n;
}

/**
 * Writeback stage implementation
 */
void writeback() {
    wb_out_n     = nop;
    wb_ld_out_n  = nop;

    we_wb        = 0;
    ws_wb        = 0;
    dout_wb      = 0;

    we_ld_wb     = 0;
    ws_ld_wb     = 0;
    dout_ld_wb   = 0;

    if (ex_out.valid) {
        wb_out_n = ex_out;
    } else if (st_out.valid) {
        wb_out_n = st_out;
    }

    /* ===================== IN-ORDER MODE ===================== */
    if (!ooo_enabled) {
        if (wb_ld_out.valid &&
            wb_ld_out.opcode == ITYPE_LOAD) {
            wb_out_n = wb_ld_out;
        }

        if (wb_out_n.valid) {
            switch (wb_out_n.opcode) {
                case ITYPE_ARITH:
                    registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                    we_wb   = 1;
                    ws_wb   = wb_out_n.rd;
                    dout_wb = wb_out_n.alu_out;
                    break;

                case RTYPE:
                    if (wb_out_n.rd != 0) {
                        registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                        we_wb   = 1;
                        ws_wb   = wb_out_n.rd;
                        dout_wb = wb_out_n.alu_out;
                    }
                    break;

                case ITYPE_LOAD:
                    if (wb_out_n.rd != 0) {
                        registers[wb_out_n.rd] = (int)wb_out_n.mem_buffer;
                        we_wb   = 1;
                        ws_wb   = wb_out_n.rd;
                        dout_wb = wb_out_n.mem_buffer;
                    }
                    break;

                case LUI:
                    if (wb_out_n.rd != 0) {
                        registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                        we_wb   = 1;
                        ws_wb   = wb_out_n.rd;
                        dout_wb = wb_out_n.alu_out;
                    }
                    break;

                case JAL:
                case JALR:
                    if (wb_out_n.rd != 0) {
                        registers[wb_out_n.rd] = (int)wb_out_n.link_addr;
                        we_wb   = 1;
                        ws_wb   = wb_out_n.rd;
                        dout_wb = wb_out_n.link_addr;
                    }
                    break;

                default:
                    break;
            }
        }

        wb_ld_out_n = nop;
        return;
    }

    /* ===================== OOO MODE: TWO WRITEBACKS ===================== */
    if (wb_out_n.valid) {
        switch (wb_out_n.opcode) {
            case ITYPE_ARITH:
                registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                we_wb   = 1;
                ws_wb   = wb_out_n.rd;
                dout_wb = wb_out_n.alu_out;
                break;

            case RTYPE:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                    we_wb   = 1;
                    ws_wb   = wb_out_n.rd;
                    dout_wb = wb_out_n.alu_out;
                }
                break;

            case ITYPE_LOAD:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.mem_buffer;
                    we_wb   = 1;
                    ws_wb   = wb_out_n.rd;
                    dout_wb = wb_out_n.mem_buffer;
                }
                break;

            case LUI:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                    we_wb   = 1;
                    ws_wb   = wb_out_n.rd;
                    dout_wb = wb_out_n.alu_out;
                }
                break;

            case JAL:
            case JALR:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.link_addr;
                    we_wb   = 1;
                    ws_wb   = wb_out_n.rd;
                    dout_wb = wb_out_n.link_addr;
                }
                break;

            default:
                break;
        }
    }

    if (wb_ld_out.valid && wb_ld_out.opcode == ITYPE_LOAD) {
        wb_ld_out_n = wb_ld_out;

        if (wb_ld_out_n.rd != 0) {
            unsigned int rd_ld = wb_ld_out_n.rd;
            registers[rd_ld] = (int)wb_ld_out_n.mem_buffer;

            // advertise this writeback to the hazard / forwarding network
            we_ld_wb   = 1;
            ws_ld_wb   = rd_ld;
            dout_ld_wb = wb_ld_out_n.mem_buffer;
        }
    } else {
        wb_ld_out_n = nop;
    }
}



/**
 * Advance PC.
 * DO NOT MODIFY.
 */

void advance_pc(int step) {
    pc_n = step;
}
