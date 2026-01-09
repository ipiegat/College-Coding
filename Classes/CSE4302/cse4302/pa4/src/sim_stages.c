/**
 * University of Connecticut
 * CSE 4302: Computer Architecture
 * Fall 2025
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
int pipe_trace_mode = 3; /* See PA1 handout, section 5 for usage */

unsigned int fetch_age = 1;

/**
 * Fetch stage implementation.
 */
void fetch() {
    fetch_out_n = nop;
    fetch2_out_n = nop;

    /* Flush on branch mispredict or jump taken */
    if (br_mispredicted || j_taken) {
        br_mispredicted = 0;
        j_taken = 0;
        return;
    }

    /* Start with old instructions if the corresponding decode pipe stalled */
    if (pipe_stall1) {
        fetch_out_n = fetch_out;     
    } 

    if (pipe_stall2) {
        fetch2_out_n = fetch2_out;  
    }

    unsigned int next_pc = pc;
    int new_fetched = 0;

    /* If pipe 1 did NOT stall, we can fetch a new instruction into slot 1 */
    if (!pipe_stall1) {
        fetch_out_n.inst_addr = next_pc;
        fetch_out_n.inst = memory[next_pc / 4];
        fetch_out_n.valid = 1;
        fetch_out_n.age = fetch_age++;   /* older than any later fetches */
        new_fetched++;
        next_pc += 4;
    }

    /* If pipe 2 did NOT stall, we can fetch a new instruction into slot 2 */
    if (!pipe_stall2) {
        fetch2_out_n.inst_addr = next_pc;
        fetch2_out_n.inst = memory[next_pc / 4];
        fetch2_out_n.valid = 1;
        fetch2_out_n.age = fetch_age++;  /* younger than whatever we just put in pipe 1 */
        new_fetched++;
        next_pc += 4;
    }


    /* Advance PC only by the number of NEW instructions fetched */
    if (new_fetched > 0) {
        advance_pc(pc + 4 * new_fetched);
    }
    /* If new_fetched == 0 (both stalled), PC does not change */
}

// helper function for decode
static void prepare_decode_inst(struct State *inst, unsigned int rs1_val, unsigned int rs2_val) {
    if (!inst->valid) return;

    uint32_t opcode = inst->opcode;

    inst->alu_in1 = rs1_val;
    inst->alu_in2 = rs2_val;

    switch (opcode) {
        case RTYPE:
            break;

        case ITYPE_ARITH:
            inst->alu_in2 = (uint32_t)inst->imm;
            if (inst->imm & 0x800) inst->imm |= 0xFFFFF000;
            break;

        case ITYPE_LOAD:
            inst->alu_in2 = (uint32_t)inst->imm;
            break;

        case STYPE:
            inst->alu_in2 = (uint32_t)inst->imm;
            inst->mem_buffer = rs2_val;
            break;

        case BTYPE:
            inst->br_addr = inst->inst_addr + (uint32_t)inst->imm;
            break;

        case JAL:
            inst->link_addr = inst->inst_addr + 4u;
            inst->br_addr = inst->inst_addr + (uint32_t)inst->imm;
            j_taken = 1;
            advance_pc(inst->br_addr);
            break;

        case JALR: {
            inst->alu_in2 = (uint32_t)inst->imm;
            unsigned int target = (inst->alu_in1 + inst->alu_in2) & ~1u;
            inst->link_addr = inst->inst_addr + 4u;
            inst->br_addr = target;
            j_taken = 1;
            advance_pc(inst->br_addr);
            break;
        }

        case LUI:
            inst->alu_in1 = 0u;
            inst->alu_in2 = (uint32_t)(inst->inst & bit_31_downto_12);
            inst->imm = (inst->inst & bit_31_downto_12);
            break;

        default:
            break;
    }
}

/**
 * Decode stage implementation
 */
void decode() {
    
    struct State *older;
    struct State *younger;

    /*Insert your code here*/
    pipe_stall1 = 0;
    pipe_stall2 = 0;

    decode_out_n = fetch_out;
    decode2_out_n = fetch2_out;

    if (!decode_out_n.valid && !decode2_out_n.valid) {
        return;
    }

    // If br_mispredicted is asserted, both instructions in the decode stage are flushed. 
    if (br_mispredicted) {
        decode_out_n = nop;
        decode2_out_n = nop;
        return;
    }

    if (decode_out_n.age <= decode2_out_n.age) {
        older = &decode_out_n;
        younger = &decode2_out_n;
    } else {
        younger = &decode_out_n;
        older = &decode2_out_n;
    }

    if (older-> valid) decode_fields(older);
    if (younger->valid) decode_fields(younger);

    // Figure out which operands are actually needed
    int older_need_rs1 = older->valid && (
        (older->opcode == RTYPE)      ||
        (older->opcode == ITYPE_ARITH)||
        (older->opcode == ITYPE_LOAD) ||
        (older->opcode == STYPE)      ||
        (older->opcode == BTYPE)      ||
        (older->opcode == JALR));

    int older_need_rs2 = older->valid && (
        (older->opcode == RTYPE) ||
        (older->opcode == STYPE) ||
        (older->opcode == BTYPE));

    int younger_need_rs1 = younger->valid && (
        (younger->opcode == RTYPE)      ||
        (younger->opcode == ITYPE_ARITH)||
        (younger->opcode == ITYPE_LOAD) ||
        (younger->opcode == STYPE)      ||
        (younger->opcode == BTYPE)      ||
        (younger->opcode == JALR));

    int younger_need_rs2 = younger->valid && (
        (younger->opcode == RTYPE) ||
        (younger->opcode == STYPE) ||
        (younger->opcode == BTYPE));

    int older_writes_reg = older->valid && (
            older->opcode == RTYPE        ||
            older->opcode == ITYPE_ARITH  ||
            older->opcode == ITYPE_LOAD   ||
            older->opcode == LUI          ||
            older->opcode == JAL          ||
            older->opcode == JALR) && (older->rd != 0);

    int younger_writes_reg = younger->valid && (
            younger->opcode == RTYPE        ||
            younger->opcode == ITYPE_ARITH  ||
            younger->opcode == ITYPE_LOAD   ||
            younger->opcode == LUI          ||
            younger->opcode == JAL          ||
            younger->opcode == JALR) && (younger->rd != 0);


    // Read regfile values
    unsigned int older_rs1_val = older_need_rs1 ? (uint32_t)registers[older->rs1] : 0u;
    unsigned int older_rs2_val = older_need_rs2 ? (uint32_t)registers[older->rs2] : 0u;

    unsigned int younger_rs1_val = younger_need_rs1 ? (uint32_t)registers[younger->rs1] : 0u;
    unsigned int younger_rs2_val = younger_need_rs2 ? (uint32_t)registers[younger->rs2] : 0u;

    // check dependencies for older
    int older_dep_ex_rs1 = we_exe && older_need_rs1 && older->rs1 != 0 && (ws_exe == older->rs1);
    int older_dep_ex_rs2 = we_exe && older_need_rs2 && older->rs2 != 0 && (ws_exe == older->rs2);

    int older_dep_wb_rs1 = we_wb && older_need_rs1 && older->rs1 != 0 && (ws_wb == older->rs1);
    int older_dep_wb_rs2 = we_wb && older_need_rs2 && older->rs2 != 0 && (ws_wb == older->rs2);

    int older_dep_ldwb_rs1 = we_ld_wb && older_need_rs1 && older->rs1 != 0 && (ws_ld_wb == older->rs1);
    int older_dep_ldwb_rs2 = we_ld_wb && older_need_rs2 && older->rs2 != 0 && (ws_ld_wb == older->rs2);

    int older_dep_mem_rs1 = we_mem && older_need_rs1 && older->rs1 != 0 && (ws_mem == older->rs1);
    int older_dep_mem_rs2 = we_mem && older_need_rs2 && older->rs2 != 0 && (ws_mem == older->rs2);

    // check dependencies for younger
    int younger_dep_ex_rs1 = we_exe && younger_need_rs1 && younger->rs1 != 0 && (ws_exe == younger->rs1);
    int younger_dep_ex_rs2 = we_exe && younger_need_rs2 && younger->rs2 != 0 && (ws_exe == younger->rs2);

    int younger_dep_wb_rs1 = we_wb && younger_need_rs1 && younger->rs1 != 0 && (ws_wb == younger->rs1);
    int younger_dep_wb_rs2 = we_wb && younger_need_rs2 && younger->rs2 != 0 && (ws_wb == younger->rs2);

    int younger_dep_ldwb_rs1 = we_ld_wb && younger_need_rs1 && younger->rs1 != 0 && (ws_ld_wb == younger->rs1);
    int younger_dep_ldwb_rs2 = we_ld_wb && younger_need_rs2 && younger->rs2 != 0 && (ws_ld_wb == younger->rs2);

    int younger_dep_mem_rs1 = we_mem && younger_need_rs1 && younger->rs1 != 0 && (ws_mem == younger->rs1);
    int younger_dep_mem_rs2 = we_mem && younger_need_rs2 && younger->rs2 != 0 && (ws_mem == younger->rs2);

    // forwarding for older
    if (older_need_rs1) {
        if (older_dep_ex_rs1) older_rs1_val = (uint32_t)dout_exe;
        else if (older_dep_wb_rs1) older_rs1_val = (uint32_t)dout_wb;
        else if (older_dep_ldwb_rs1) older_rs1_val = (uint32_t)dout_ld_wb;
        else if (older_dep_mem_rs1 && !dmem_busy) older_rs1_val = (uint32_t)dout_mem;
    }
    if (older_need_rs2) {
        if (older_dep_ex_rs2) older_rs2_val = (uint32_t)dout_exe;
        else if (older_dep_wb_rs2) older_rs2_val = (uint32_t)dout_wb;
        else if (older_dep_ldwb_rs2) older_rs2_val = (uint32_t)dout_ld_wb;
        else if (older_dep_mem_rs2 && !dmem_busy) older_rs2_val = (uint32_t)dout_mem;
    }
    
    // forwarding for younger
    if (younger_need_rs1) {
        if (younger_dep_ex_rs1) younger_rs1_val = (uint32_t)dout_exe;
        else if (younger_dep_wb_rs1) younger_rs1_val = (uint32_t)dout_wb;
        else if (younger_dep_ldwb_rs1) younger_rs1_val = (uint32_t)dout_ld_wb;
        else if (younger_dep_mem_rs1 && !dmem_busy) younger_rs1_val = (uint32_t)dout_mem;
    }
    if (younger_need_rs2) {
        if (younger_dep_ex_rs2) younger_rs2_val = (uint32_t)dout_exe;
        else if (younger_dep_wb_rs2) younger_rs2_val = (uint32_t)dout_wb;
        else if (younger_dep_ldwb_rs2) younger_rs2_val = (uint32_t)dout_ld_wb;
        else if (younger_dep_mem_rs2 && !dmem_busy) younger_rs2_val = (uint32_t)dout_mem;
    }

    int older_is_load = older->valid && (older->opcode == ITYPE_LOAD);
    int older_is_store = older->valid && (older->opcode == STYPE);
    int older_is_terminate = older->valid && (older->opcode == ITYPE_ARITH && older->rd == 0 && older->rs1 == 0 && older->imm == 1); // addi x0,x0,1
   
    int younger_is_load = younger->valid && (younger->opcode == ITYPE_LOAD);
    int younger_is_store = younger->valid && (younger->opcode == STYPE);
    int younger_is_terminate = younger->valid && (younger->opcode == ITYPE_ARITH && younger->rd == 0 && younger->rs1 == 0 && younger->imm == 1); // addi x0,x0,1

    int older_is_jump = older->valid && (older->opcode == JAL || older->opcode == JALR);
    int older_is_branch = older->valid && (older->opcode == BTYPE);

    int older_uses_alu   = older->valid   && !older_is_load   && !older_is_store;
    int younger_uses_alu = younger->valid && !younger_is_load && !younger_is_store;

    int younger_waw_older_load = older_is_load && younger_writes_reg && (younger->rd == older->rd);
    int younger_store_war_older_load = older_is_load && younger_is_store;

    int load_unit_busy = dmem_busy;
    int load_unit_finishing = dmem_busy && (dmem_cycles == dmem_access_cycles);

    // Information about the in-flight load in the dedicated load unit
    int load_dest_valid =
        load_unit_busy &&
        ld_out_n.valid &&
        (ld_out_n.opcode == ITYPE_LOAD) &&
        (ld_out_n.rd != 0);

    // RAW hazard: this decode instruction reads the destination of the in-flight load
    int older_load_raw_hazard_rs1 =
        load_dest_valid &&
        !load_unit_finishing &&
        older_need_rs1 &&
        (older->rs1 == ld_out_n.rd);
    
    int older_load_raw_hazard_rs2 =
        load_dest_valid &&
        !load_unit_finishing &&
        older_need_rs2 &&
        (older->rs2 == ld_out_n.rd);

    int younger_load_raw_hazard_rs1 =
        load_dest_valid &&
        !load_unit_finishing &&
        younger_need_rs1 &&
        (younger->rs1 == ld_out_n.rd);

    int younger_load_raw_hazard_rs2 =
        load_dest_valid &&
        !load_unit_finishing &&
        younger_need_rs2 &&
        (younger->rs2 == ld_out_n.rd);

    int younger_raw_older_rs1 =
        older_writes_reg &&
        younger_need_rs1 &&
        (younger->rs1 == older->rd);

    int younger_raw_older_rs2 =
        older_writes_reg &&
        younger_need_rs2 &&
        (younger->rs2 == older->rd);


    // stall logic
    int younger_raw_older = younger_raw_older_rs1 || younger_raw_older_rs2;
    int older_load_raw = older_load_raw_hazard_rs1 || older_load_raw_hazard_rs2;

    int younger_load_raw = younger_load_raw_hazard_rs1 || younger_load_raw_hazard_rs2;

    int stall_older = 0;
    int stall_younger = 0;

    int older_is_slot1 = (older == &decode_out_n);
    int younger_is_slot1 = (younger == &decode_out_n);
    

    // If any of these conditions occur, the older instruction is stalled by setting its corresponding pipe_-
    // stall* signal.
    if (older->valid) {
        int older_load_structural  = older_is_load  && load_unit_busy && !load_unit_finishing;
        int older_store_structural = older_is_store && load_unit_busy && !load_unit_finishing;
        int older_term_wait = older_is_terminate && load_unit_busy && !load_unit_finishing;
        int older_waw_load =
            older_writes_reg &&
            load_dest_valid &&
            !load_unit_finishing &&
            (older->rd == ld_out_n.rd);

        if (older_load_raw ||
            older_load_structural ||
            older_store_structural ||
            older_term_wait ||
            older_waw_load) {
            stall_older = 1;
        }
    }

    if (older->valid && stall_older) {
        stall_younger = 1;
    } else if (younger->valid) {
        int younger_load_structural  = younger_is_load  && load_unit_busy && !load_unit_finishing;
        int younger_store_structural = younger_is_store && load_unit_busy && !load_unit_finishing;
        int younger_term_wait        = younger_is_terminate && older_is_load;
        int younger_alu_structural   = older_uses_alu && younger_uses_alu;

        if (younger_load_raw ||
            younger_load_structural ||
            younger_store_structural ||
            younger_term_wait ||
            younger_waw_older_load ||
            younger_store_war_older_load ||
            younger_raw_older || 
            younger_alu_structural) {
            stall_younger = 1;
        }
    }



    // If older is a branch and it is not stalled, younger must stall
    if (!stall_older && older_is_branch && younger->valid) {
        stall_younger = 1;
    }

    // If older is a jump and it is not stalled, flush the younger
    if (!stall_older && older_is_jump && older->valid && younger->valid) {
        if (younger_is_slot1) {
            decode_out_n = nop;
        } else {
            decode2_out_n = nop;
        }
        
        younger->valid = 0;
        stall_younger = 0;
    }

    if (stall_older) {
        if (older_is_slot1) {
            pipe_stall1 = 1;
            decode_out_n = nop;
        } else {
            pipe_stall2 = 1;
            decode2_out_n = nop;
        }
    }

    if (stall_younger) {
        if (younger_is_slot1) {
            pipe_stall1 = 1;
            decode_out_n = nop;
        } else {
            pipe_stall2 = 1;
            decode2_out_n = nop;
        }
    }

    if (!stall_older && older->valid) prepare_decode_inst(older, older_rs1_val, older_rs2_val);

    if (!stall_younger && younger->valid) prepare_decode_inst(younger, younger_rs1_val, younger_rs2_val);

}

/**
 * Execute stage implementation
 */

struct State execute() {
    ex_out_n = nop;
    ws_exe = 0;
    we_exe = 0;
    br_mispredicted = 0;

    int slot1_uses_alu = decode_out.valid &&
                         decode_out.opcode != ITYPE_LOAD &&
                         decode_out.opcode != STYPE;

    int slot2_uses_alu = decode2_out.valid &&
                         decode2_out.opcode != ITYPE_LOAD &&
                         decode2_out.opcode != STYPE;

    if (slot1_uses_alu && !slot2_uses_alu) {
        ex_out_n = decode_out;
    } else if (!slot1_uses_alu && slot2_uses_alu) {
        ex_out_n = decode2_out;
    } else if (slot1_uses_alu && slot2_uses_alu) {
        if (decode_out.age <= decode2_out.age) {
            ex_out_n = decode_out;   // older ALU user
        } else {
            ex_out_n = decode2_out;  // older ALU user
        }
    } else {
        return ex_out_n;            // no ALU work this cycle
    }

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
            unsigned int r1 = ex_out_n.alu_in1;
            unsigned int r2 = ex_out_n.alu_in2;

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
 * Execute stage implementation for Load 
 */
struct State load_stage() {
    ld_out_n = ld_out;
    wb_ld_out_n = nop;

    we_mem = 0;
    ws_mem = 0;
    dout_mem = 0;

    if (!dmem_busy) {
        int slot1_can_load = decode_out.valid &&
                             decode_out.opcode == ITYPE_LOAD &&
                             !pipe_stall1;

        int slot2_can_load = decode2_out.valid &&
                             decode2_out.opcode == ITYPE_LOAD &&
                             !pipe_stall2;

        if (slot1_can_load && !slot2_can_load) {
            ld_out_n = decode_out;
        } else if (!slot1_can_load && slot2_can_load) {
            ld_out_n = decode2_out;
        } else if (slot1_can_load && slot2_can_load) {
            if (decode_out.age <= decode2_out.age) {
                ld_out_n = decode_out;
            } else {
                ld_out_n = decode2_out;
            }
        } else {
            return ld_out_n;
        }

        unsigned int base = ld_out_n.alu_in1;
        unsigned int off  = ld_out_n.alu_in2;
        ld_out_n.mem_addr = base + off;

        dmem_busy   = 1;
        dmem_cycles = 0;

    } else if (ld_out.valid) {
        dmem_cycles++;
        if (dmem_cycles >= dmem_access_cycles) {
            unsigned int addr = ld_out.mem_addr;
            ld_out.mem_buffer = memory[addr];

            wb_ld_out_n = ld_out;

            if (ld_out.rd != 0) {
                we_mem = 1;
                ws_mem = ld_out.rd;
                dout_mem = ld_out.mem_buffer;
            }

            ld_out_n = nop;
            dmem_busy = 0;
            dmem_cycles = 0;
        }
    }

    return ld_out_n;
}





/**
 * Execute stage implementation for Stores
 */
struct State store_stage() {
    st_out_n = st_out;
    wb_st_out_n = nop;

    int slot1_can_store = decode_out.valid &&
                          decode_out.opcode == STYPE &&
                          !pipe_stall1;

    int slot2_can_store = decode2_out.valid &&
                          decode2_out.opcode == STYPE &&
                          !pipe_stall2;

    if (slot1_can_store && !slot2_can_store) {
        st_out_n = decode_out;
    } else if (!slot1_can_store && slot2_can_store) {
        st_out_n = decode2_out;
    } else if (slot1_can_store && slot2_can_store) {
        if (decode_out.age <= decode2_out.age) {
            st_out_n = decode_out;   // older store
        } else {
            st_out_n = decode2_out;  // older store
        }
    } else {
        // no store issues this cycle
        return st_out_n;
    }

    if (st_out_n.opcode == STYPE && st_out_n.valid) {
        unsigned int base = st_out_n.alu_in1;  // rs1 value
        unsigned int off  = st_out_n.alu_in2;  // imm
        unsigned int addr = base + off;
        memory[addr] = st_out_n.mem_buffer;   // <<< important: /4

        wb_st_out_n = st_out_n;
        st_out_n = nop;
    }

    return st_out_n;
}


/**
 * Writeback stage implementation
 */
void writeback() {
    wb_out_n = nop;
    wb_ld_out_n = nop;
    wb_st_out_n = nop;

    we_wb = 0;
    ws_wb = 0;
    dout_wb = 0;

    we_ld_wb = 0;
    ws_ld_wb = 0;
    dout_ld_wb = 0;

    if (ex_out.valid) {
        wb_out_n = ex_out;

        switch (wb_out_n.opcode) {
            case ITYPE_ARITH:
                registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                we_wb = 1;
                ws_wb = wb_out_n.rd;
                dout_wb = wb_out_n.alu_out;
                break;

            case RTYPE:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                    we_wb = 1;
                    ws_wb = wb_out_n.rd;
                    dout_wb = wb_out_n.alu_out;
                }
                break;

            case LUI:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                    we_wb = 1;
                    ws_wb = wb_out_n.rd;
                    dout_wb = wb_out_n.alu_out;
                }
                break;

            case JAL:
            case JALR:
                if (wb_out_n.rd != 0) {
                    registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
                    we_wb = 1;
                    ws_wb = wb_out_n.rd;
                    dout_wb = wb_out_n.alu_out;
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

            we_ld_wb   = 1;
            ws_ld_wb   = rd_ld;
            dout_ld_wb = wb_ld_out_n.mem_buffer;
        }
    } else {
        wb_ld_out_n = nop;
    }

    if (wb_st_out.valid && wb_st_out.opcode == STYPE) {
        wb_st_out_n = wb_st_out;
    } else {
        wb_st_out_n = nop;
    }
}


/**
 * Advance PC.
 * DO NOT MODIFY.
 */

void advance_pc(int step) {
    pc_n = step;
}
