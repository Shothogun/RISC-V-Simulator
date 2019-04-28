#ifndef FEC_H
#define FEC_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern uint32_t pc, ri, sp, gp;

extern int32_t opcode, rs1, rs2, rt, rd, 
               shamt, funct3, funct7, imm12_i, imm12_s, imm13, imm20_u, imm21;

void read_bin();
void fetch();
void decode();

#endif