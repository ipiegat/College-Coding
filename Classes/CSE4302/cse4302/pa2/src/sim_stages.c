/**
 * University of Connecticut
 * CSE 4302: Computer Architecture
 * Fall 2025
 * 
 * Programming Assignment 2: Pipelined Simulator
 * 
 * riscy-uconn: sim_stages.c
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "instruction_map.h"
#include "sim_core.h"
#include "sim_stages.h"
#include "decode_fields.h"

/**
 * Debug flags
 */
int debug = 0;          // Set to 1 for additional debugging information.
int pipe_trace = 1;     // Set to 1 for pipe trace.
int pipe_trace_mode = 3;

/* Pipeline related */
int pipe_stall      = 0;
int j_taken         = 0;
int br_mispredicted = 0;
int we_exe          = 0, ws_exe   = 0, dout_exe = 0;
int we_wb           = 0, ws_wb    = 0, dout_wb  = 0;

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
    // read the fetch_out state and start processing decode functionality 
    decode_out_n = fetch_out;
    
    /*Insert your code here*/
    pipe_stall = 0;

    // return nop if br_mispredicted
    if (br_mispredicted) {
        decode_out_n = nop;
        return decode_out_n;
    }

    decode_fields(&decode_out_n);

    int rs1 = decode_out_n.rs1;
    int rs2 = decode_out_n.rs2;

    int dep_ex_rs1 = we_exe && rs1 != 0 && (ws_exe == rs1);



    int dep_ex_rs2 = we_exe && rs2 != 0 && (ws_exe == rs2);
    int dep_wb_rs1 = we_wb  && rs1 != 0 && (ws_wb  == rs1);
    int dep_wb_rs2 = we_wb  && rs2 != 0 && (ws_wb  == rs2);

    // Does this instruction need rs1
    int need_rs1 = (decode_out_n.opcode == RTYPE)    ||
                (decode_out_n.opcode == ITYPE_ARITH)  ||
                (decode_out_n.opcode == ITYPE_LOAD)   ||
                (decode_out_n.opcode == STYPE)        ||
                (decode_out_n.opcode == BTYPE)        ||
                (decode_out_n.opcode == JALR);

    // Does this instruction need rs2
    int need_rs2 = (decode_out_n.opcode == RTYPE) ||
                (decode_out_n.opcode == STYPE) ||
                (decode_out_n.opcode == BTYPE);

    unsigned int rs1_val = (need_rs1 ? (uint32_t)registers[rs1] : 0u);
    unsigned int rs2_val = (need_rs2 ? (uint32_t)registers[rs2] : 0u);

    if (forwarding_enabled) {
        if (need_rs1) {
            if (dep_ex_rs1)      rs1_val = (uint32_t)dout_exe;
            else if (dep_wb_rs1) rs1_val = (uint32_t)dout_wb;
        }
        if (need_rs2) {
            if (dep_ex_rs2)      rs2_val = (uint32_t)dout_exe;
            else if (dep_wb_rs2) rs2_val = (uint32_t)dout_wb;
        }
    }
    

    if (!forwarding_enabled) {
        if ((need_rs1 && (dep_ex_rs1 || dep_wb_rs1)) ||
                (need_rs2 && (dep_ex_rs2 || dep_wb_rs2))) {
            pipe_stall = 1;
            decode_out_n = nop;
            return decode_out_n;
        }
    }

    decode_out_n.alu_in1 = rs1_val;
    decode_out_n.alu_in2 = rs2_val;

    switch (decode_out_n.opcode) {
        case RTYPE:
            break;

        case ITYPE_ARITH:
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            if (decode_out_n.imm & 0x800) decode_out_n.imm |= 0xFFFFF000;
            break;

        case ITYPE_LOAD:
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            break;

        case STYPE:
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            decode_out_n.mem_buffer = rs2_val;
            break;

        case BTYPE:
            decode_out_n.br_addr = decode_out_n.inst_addr + (uint32_t)decode_out_n.imm;
            break;

        case JAL:
            decode_out_n.link_addr = decode_out_n.inst_addr + 4u;
            decode_out_n.br_addr = decode_out_n.inst_addr + (uint32_t)decode_out_n.imm;
            j_taken = 1;
            decode_out_n.br_taken = 1;
            advance_pc(decode_out_n.br_addr);
            break;

        case JALR: {
            decode_out_n.alu_in2 = (uint32_t)decode_out_n.imm;
            unsigned int target = (decode_out_n.alu_in1 + decode_out_n.alu_in2) & ~1u;
            decode_out_n.link_addr = decode_out_n.inst_addr + 4u;
            decode_out_n.br_addr = target;
            decode_out_n.br_taken = 1;
            j_taken = 1;
            advance_pc(decode_out_n.br_addr);
            break;
        }

        case LUI:
            decode_out_n.alu_in1 = 0u;



            decode_out_n.alu_in2 = (uint32_t)(decode_out_n.inst & bit_31_downto_12);
            decode_out_n.imm = (decode_out_n.inst & bit_31_downto_12);
            break;

        default:
            break;
    }

    //Return the instruction
    return decode_out_n;
}

/**
 * Execute stage implementation
 */
struct State execute() {
    ex_out_n = decode_out;

    if (!ex_out_n.valid) {
        we_exe = 0; ws_exe = 0; dout_exe = 0;
        return ex_out_n;
    }

    we_exe = 0;
    ws_exe = 0;

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
                        ex_out_n.alu_out = (sh == 0) ? r1 : ((r1 >> sh) | ((r1 & 0x80000000u) ? (~0u << (32 - sh)) : 0u));
                    } else {
                        ex_out_n.alu_out = r1 >> sh;
                    }
                    break;
                }
                default: ex_out_n.alu_out = 0; break;
            }
            if (ex_out_n.rd != 0) { we_exe = 1; ws_exe = ex_out_n.rd; dout_exe = ex_out_n.alu_out; }
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
                    if (((r2 >> 5) & 0x7F) == SUB_F7) {
                        ex_out_n.alu_out = (shamt == 0) ? r1 : ((r1 >> shamt) | ((r1 & 0x80000000u) ? (~0u << (32 - shamt)) : 0u));
                    } else {
                        ex_out_n.alu_out = r1 >> shamt;
                    }
                    break;
                }
                default: ex_out_n.alu_out = 0; break;
            }
            if (ex_out_n.rd != 0) { we_exe = 1; ws_exe = ex_out_n.rd; dout_exe = ex_out_n.alu_out; }
            break;
        }

        case ITYPE_LOAD: {
            ex_out_n.mem_addr = r1 + r2;
            ex_out_n.mem_buffer = memory[ex_out_n.mem_addr];
            if (ex_out_n.rd != 0) { we_exe = 1; ws_exe = ex_out_n.rd; dout_exe = ex_out_n.mem_buffer; }
            break;
        }

        case STYPE: {
            ex_out_n.mem_addr = r1 + r2;
            memory[ex_out_n.mem_addr] = ex_out_n.mem_buffer;
            break;
        }

        case BTYPE: {
            ex_out_n.br_taken = 0;
            switch (funct3) {
                case BEQ: ex_out_n.br_taken = (r1 == r2); break;
                case BNE: ex_out_n.br_taken = (r1 != r2); break;
                case BLT: {
                    unsigned int s1 = r1 ^ 0x80000000u;
                    unsigned int s2 = r2 ^ 0x80000000u;
                    ex_out_n.br_taken = (s1 < s2);
                    break;
                }
                case BGE: {
                    unsigned int s1 = r1 ^ 0x80000000u;
                    unsigned int s2 = r2 ^ 0x80000000u;
                    ex_out_n.br_taken = (s1 >= s2);
                    break;
                }
                default: break;
            }
            if (ex_out_n.br_taken) {
                ex_out_n.br_addr = ex_out_n.inst_addr + (unsigned int)ex_out_n.imm;
                advance_pc(ex_out_n.br_addr);
                br_mispredicted = 1;
            }
            break;
        }

        case JAL:
        case JALR:
            ex_out_n.alu_out = ex_out_n.link_addr;
            if (ex_out_n.rd != 0) { we_exe = 1; ws_exe = ex_out_n.rd; dout_exe = ex_out_n.alu_out; }
            break;

        case LUI:
            ex_out_n.alu_out = (uint32_t)ex_out_n.imm;
            if (ex_out_n.rd != 0) { we_exe = 1; ws_exe = ex_out_n.rd; dout_exe = ex_out_n.alu_out; }
            break;

        default:
            break;
    }

    return ex_out_n;
}

/**
 * Writeback stage implementation
 */
struct State writeback() {
    wb_out_n = ex_out;

    we_wb = 0;
    ws_wb = 0;
    
    if (!wb_out_n.valid) {
        wb_out_n = nop;
        return wb_out_n;
    }

    switch (wb_out_n.opcode) {
        case RTYPE:
            if (wb_out_n.rd != 0) registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
            break;
        case ITYPE_ARITH:
            registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
            break;
        case LUI:
            if (wb_out_n.rd != 0) registers[wb_out_n.rd] = (int)wb_out_n.alu_out;
            break;
        case ITYPE_LOAD:
            if (wb_out_n.rd != 0) registers[wb_out_n.rd] = (int)wb_out_n.mem_buffer;
            break;
        case JALR:
            if (wb_out_n.rd != 0) registers[wb_out_n.rd] = (int)wb_out_n.link_addr;
            break;
        case JAL:
            if (wb_out_n.rd != 0) registers[wb_out_n.rd] = (int)wb_out_n.link_addr; 
            break;
    }

    if (wb_out_n.opcode == RTYPE || 
        wb_out_n.opcode == ITYPE_ARITH || 
        wb_out_n.opcode == ITYPE_LOAD ||
        wb_out_n.opcode == LUI ||
        wb_out_n.opcode == JAL ||
        wb_out_n.opcode == JALR)
    {
        if (wb_out_n.rd != 0) {
            we_wb = 1;
            ws_wb = wb_out_n.rd;
        }
    }

    if (we_wb) {
        if (wb_out_n.opcode == RTYPE || 
            wb_out_n.opcode == ITYPE_ARITH || 
            wb_out_n.opcode == LUI) {

            dout_wb = wb_out_n.alu_out;
        } else if (wb_out_n.opcode == ITYPE_LOAD) {
            dout_wb = wb_out_n.mem_buffer;
        } else if (wb_out_n.opcode == JAL || wb_out_n.opcode == JALR) {
            dout_wb = wb_out_n.link_addr;
        }
    }

    return wb_out_n;
}

/**
 * Advance PC.
 * DO NOT MODIFY.
 */

void advance_pc(int step) {
    pc_n = step;
}
