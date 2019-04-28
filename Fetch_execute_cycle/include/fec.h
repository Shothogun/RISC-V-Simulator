#ifndef FEC_H
#define FEC_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern uint32_t pc, ri, sp, gp;
extern int32_t opcode, rs, rt, rd, shamt, funct;

void read_bin();

#endif