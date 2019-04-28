#include "./include/RISCV_mem.h"

int main(){
  read_bin();

  // Sucessive intructions in machine language
  printf("***Teste de leitura de arquivo e salvar em memoria***\n");
  printf("\t***Leitura sucessiva de instrucoes***\n");
  printf("\t\t%.8X\n",mem[0]);
  printf("\t\t%.8X\n",mem[1]);
  printf("\t\t%.8X\n",mem[2]);
  printf("\t\t%.8X\n",mem[3]);
  printf("\t\t%.8X\n",mem[4]);

  // Last instruction
  printf("\t***Ultima instrucao***\n");
  printf("\t\t%.8X\n",mem[21]);

  // Sucessive data in machine language
  printf("\t***Leitura sucessiva de dados***\n");
  printf("\t\t%.8X\n",mem[22]);
  printf("\t\t%.8X\n",mem[23]);
  printf("\t\t%.8X\n",mem[24]);
  printf("\t\t%.8X\n",mem[25]);
  printf("\t\t%.8X\n",mem[26]);
  
  return 0;
}