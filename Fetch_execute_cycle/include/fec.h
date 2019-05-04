#ifndef FEC_H
#define FEC_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern uint32_t pc, ri;

extern int32_t opcode, rs1, rs2, rt, rd, 
               shamt, funct3, funct7, imm12_i, imm12_s, imm13, imm20_u, imm21;

typedef enum {
  // registros de sistema 
  zero = 0, ra = 1, sp = 2,   gp = 3, tp = 4, fp = 8,                   

  // registros tipo t
  t0 = 5, t1 = 6, t2 = 7, t3 = 28, t4 = 29, t5 = 30, t6 = 31,           

  // registros tipo s
  s1 = 9, s2 = 18, s3 = 19, s4 = 20, s5 = 21, s6 = 22,                  
  s7 = 23 , s8 = 24, s9 = 25, s10 = 26, s11 = 27,                       

  // registros tipo a 
  a0 = 10, a1 = 11, a2 = 12,                                                                
  a3 = 13, a4 = 14, a5 = 15, a6 = 16, a7 = 17,                          
} BREG;

typedef enum {                        // lembrem que so sao considerados os 7 primeiros bits dessas constantes
  LUI = 0x37,     AUIPC = 0x17,       // atribui 20 bits mais significativos
  ILType = 0x03,                      // Load type
  BType = 0x63,                       // branch condicional
  JAL = 0x6F,     JALR = 0x67,        // jumps - JAL formato UJ, JALR formato I
  StoreType = 0x23,                   // store
  ILAType = 0x13,                     // logico-aritmeticas com imediato
  RegType = 0x33,                     // operacoes LA com registradores
  ECALL = 0x73                        // chamada do sistema - formato I
} OPCODES;

typedef enum {                                                      //campo auxiliar de 3 bits
  BEQ3=0, BNE3=01, BLT3=04, BGE3=05, BLTU3=0x06, BGEU3=07,          //branches
  LB3=0, LH3=01, LW3=02, LBU3=04, LHU3=05,                          //loads
  SB3=0, SH3=01, SW3=02,                                            //stores
  ADDSUB3=0, SLL3=01, SLT3=02, SLTU3=03,                            //LA com
  XOR3=04, SR3=05,                                                  //registradores
  OR3=06, AND3=07, ADDI3=0, ORI3=06, SLTI3=02, XORI3=04, ANDI3=07,  //LA com
  SLTIU3=03, SLLI3=01, SRI3=05                                      //imediatos
} FUNCT3;

typedef enum {
  // campo auxiliar de 7 bits para as instrucoes SRLI/SRAI, ADD/SUB, SRL/SRA
  ADD7=0, SUB7=0x20, SRA7=0x20, SRL7=0, SRLI7=0x00, SRAI7=0x20
} FUNCT7;

typedef enum {
  // Comandos syscall
  SYS_PRINT_INT=1, SYS_PRINT_STRING=4, SYS_PRINT_CHAR = 11, SYS_EXIT = 10
} A7;

void read_bin();
void fetch();
void decode();
void execute();

#endif