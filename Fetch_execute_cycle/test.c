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
  printf("\t\t%.8X\n",mem[DATA+1]);
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
  printf("\timm20:\t\t%.8X\n\n", imm13);

  // Execute
  printf("***Execute***\n\n");

  // LUI instruction
  printf("***Teste instrucao LUI***\n\n");
  opcode = LUI;              
  imm20_u = 0xFFFFCAFE;
  rd = t0;                     // t1 register

  execute();

  printf("\topcode: %X\n", LUI);
  printf("\tValor no imm20_u: %.8X\n", imm20_u);
  printf("\tValor no registro: %.8X\n\n",breg[rd]);

  // AUIPC instruction
  printf("***Teste instrucao AUIPC***\n\n");
  opcode = AUIPC;
  pc = 0x4;   
  imm20_u = 0x0001234B;
  rd = t2;                     // t2 register

  execute();

  printf("\topcode: %X\n", AUIPC);
  printf("\tValor no imm20_u: %.8X\n", imm20_u);
  printf("\tValor no registro: %.8X\n\n",breg[rd]);

  // ILType instruction
  printf("***Teste instrucao ILType***\n\n");  
  opcode = ILType;

    // LB instruction
    printf("\t***Teste instrucao load byte***\n\n");

    funct3 = LB3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2000;           // first data value stored in previous read bin
                                  // test(1)

    imm12_i = 0;                  // offset

    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    printf("\t***Segundo Teste instrucao load byte***\n\n");

    mem[DATA+1] = 0xA3;            // byte stored

    funct3 = LB3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2004;           // byte address

    imm12_i = 0;                  // offset

    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    // LH instruction
    printf("\t***Teste instrucao load half***\n\n");

    mem[DATA] = 0xCAFE;           // Half word stored
    funct3 = LH3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2000;           // Half word address

    imm12_i = 0;                  // offset

    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    // LW instruction
    printf("\t***Teste instrucao load word***\n\n");

    mem[DATA] = 0xABCDCAFE;       // word stored
    funct3 = LW3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2000;           // word address

    imm12_i = 0;                  // offset

    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    // Lbu instruction
    printf("\t***Teste instrucao load byte unsigned***\n\n");

    mem[DATA] = 0xA3;            // byte unsigned stored
    funct3 = LBU3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2000;          // byte address

    imm12_i = 0;                 // offset

    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    // Lhu instruction
    printf("\t***Teste instrucao load half unsigned***\n\n");

    mem[DATA] = 0xCAFE;          // Half word unsigned stored
    funct3 = LHU3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2000;          // Half word address

    imm12_i = 0;                 // offset

    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);
  
  // opcode instruction
  printf("***Teste instrucao Store***\n\n");  
  opcode = StoreType;

    printf("\t***Teste instrucao Store byte***\n\n");  
    // SB instruction

    funct3 = SB3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2000;           // Destiny addres
    breg[rs2] = 0xAB;             // value stored
    imm12_s = 2;
    
    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", imm12_s);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de rs1: %.8X\n\n", mem[breg[rs1]>>2]);

    printf("\t***Teste instrucao Store half***\n\n");  
    // SH instruction

    funct3 = SH3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2000;           // Destiny addres
    breg[rs2] = 0xABAC;           // value stored
    imm12_s = 2;
    
    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", imm12_s);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de rs1: %.8X\n\n", mem[breg[rs1]>>2]);

    printf("\t***Teste instrucao Store word***\n\n");  

    // Sw instruction

    funct3 = SW3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2000;           // Destiny addres
    breg[rs2] = 0xABACACAE;       // value stored
    imm12_s = 0;
    
    execute();

    printf("\topcode: %X\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", imm12_s);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de rs1: %.8X\n", mem[breg[rs1]>>2]);

  return 0;
}