#include "./include/RISCV_mem.h"
#include "fec.h"

int main(){
  read_bin();

  // Sucessive intructions in machine language
  printf("***Teste de leitura de arquivo e salvar em memoria***\n\n");
  printf("\t***Leitura sucessiva de instrucoes***\n");
  printf("\t\t%.8X\n",mem[0]);
  printf("\t\t%.8X\n",mem[1]);
  printf("\t\t%.8X\n",mem[2]);
  printf("\t\t%.8X\n",mem[3]);
  printf("\t\t%.8X\n",mem[4]);

  // Last instruction
  printf("\t***Ultima instrucao***\n\n");
  printf("\t\t%.8X\n",mem[21]);

  // Sucessive data in machine language
  printf("\t***Leitura sucessiva de dados***\n");
  printf("\t\t%.8X\n",mem[DATA]);
  printf("\t\t%.8X\n",mem[DATA+2]);
  printf("\t\t%.8X\n",mem[DATA+3]);
  printf("\t\t%.8X\n",mem[DATA+4]);
  printf("\t\t%.8X\n\n",mem[DATA+5]);

  // Decoding
  printf("***Fetch***\n\n");
  fetch();
  printf("\tri:\t\t%.8X\n", ri);
  printf("\tpc:\t\t%.8X\n\n", pc);
  decode();
  printf("***Decoding***\n\n");
  printf("\topcode:\t\t%.8X\n", opcode);
  printf("\trd:\t\t%.8X\n", rd);
  printf("\tfunct3:\t\t%.8X\n", funct3);
  printf("\trs1:\t\t%.8X\n", rs1);
  printf("\tshamt:\t\t%.8X\n", shamt);
  printf("\trs2:\t\t%.8X\n", rs2);
  printf("\tfunct7:\t\t%.8X\n", funct7);
  printf("\timm12_i:\t%.8X\n", imm12_i);
  printf("\timm12_s:\t%.8X\n", imm12_s);
  printf("\timm13:\t\t%.8X\n", imm13);
  printf("\timm20:\t\t%.8X\n", imm13);

  printf("\t***Next instruction***\n\n");
  printf("***Fetch***\n\n");
  fetch();
  printf("\tri:\t\t%.8X\n", ri);
  printf("\tpc:\t\t%.8X\n\n", pc);
  decode();
  printf("***Decoding***\n\n");
  printf("\topcode:\t\t%.8X\n", opcode);
  printf("\trd:\t\t%.8X\n", rd);
  printf("\tfunct3:\t\t%.8X\n", funct3);
  printf("\trs1:\t\t%.8X\n", rs1);
  printf("\tshamt:\t\t%.8X\n", shamt);
  printf("\trs2:\t\t%.8X\n", rs2);
  printf("\tfunct7:\t\t%.8X\n", funct7);
  printf("\timm12_i:\t%.8X\n", imm12_i);
  printf("\timm12_s:\t%.8X\n", imm12_s);
  printf("\timm13:\t\t%.8X\n", imm13);
  printf("\timm20:\t\t%.8X\n", imm13);

  printf("\t***Next instruction***\n\n");
  printf("***Fetch***\n\n");
  fetch();
  printf("\tri:\t\t%.8X\n", ri);
  printf("\tpc:\t\t%.8X\n\n", pc);
  decode();
  printf("***Decoding***\n\n");
  printf("\topcode:\t\t%.8X\n", opcode);
  printf("\trd:\t\t%.8X\n", rd);
  printf("\tfunct3:\t\t%.8X\n", funct3);
  printf("\trs1:\t\t%.8X\n", rs1);
  printf("\tshamt:\t\t%.8X\n", shamt);
  printf("\trs2:\t\t%.8X\n", rs2);
  printf("\tfunct7:\t\t%.8X\n", funct7);
  printf("\timm12_i:\t%.8X\n", imm12_i);
  printf("\timm12_s:\t%.8X\n", imm12_s);
  printf("\timm13:\t\t%.8X\n", imm13);
  printf("\timm20:\t\t%.8X\n", imm13);
  
  return 0;
}