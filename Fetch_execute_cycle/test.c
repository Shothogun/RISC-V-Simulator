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
  printf("\tValor de pc: %.8X\n", pc-4);
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

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor nesse endereço: %.8X\n", mem[breg[rs1]>>2]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    printf("\t***Segundo Teste instrucao load byte***\n\n");

    mem[DATA+1] = 0xA3;            // byte stored

    funct3 = LB3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2004;           // byte address

    imm12_i = 0;                  // offset

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor nesse endereço: %.8X\n", mem[breg[rs1]>>2]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);

    printf("\t***Terceiro Teste instrucao load byte(offset negativo)***\n\n");

    mem[DATA] = 0x0000B4A3;            // byte stored

    funct3 = LB3;
    rd = t1;
    rs1 = t0;
    breg[rs1] = 0x2003;           // byte address

    imm12_i = 0xFFE;                  // offset

    // extend signal 

    imm12_i <<= 20;
    imm12_i >>= 20;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", 0xFFE);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor no endereço 0x2000: %.8X\n", mem[breg[rs1]>>2]);
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

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor nesse endereço: %.8X\n", mem[breg[rs1]>>2]);
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

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor nesse endereço: %.8X\n", mem[breg[rs1]>>2]);
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

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor nesse endereço: %.8X\n", mem[breg[rs1]>>2]);
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

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_i): %.8X\n", imm12_i);
    printf("\tValor no registro de endereço: %.8X\n",breg[rs1]);
    printf("\tValor nesse endereço: %.8X\n", mem[breg[rs1]>>2]);
    printf("\tValor no registro destino: %.8X\n\n", breg[rd]);
  
  // StoreType instruction
  printf("***Teste instrucao Store***\n\n");  
  opcode = StoreType;

  printf("Valor anterior em 0x2000: 0x0000CAFE\n\n");  

    printf("\t***Teste instrucao Store byte***\n\n");  
    // SB instruction

    funct3 = SB3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2001;           // Destiny addres
    breg[rs2] = 0xAB;             // value stored
    imm12_s = 2;
    
    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", imm12_s);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de 0x2000: %.8X\n\n", mem[breg[rs1]>>2]);

    printf("\t***Teste instrucao Store byte(offset negativo)***\n\n");  
    // SB instruction

    funct3 = SB3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2003;           // Destiny addres
    breg[rs2] = 0xCD;             // value stored
    imm12_s = 0xFFF;

    // extend signal 

    imm12_s <<= 20;
    imm12_s >>= 20;
  
    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", 0xFFF);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de 0x2000: %.8X\n\n", mem[breg[rs1]>>2]);

    

    printf("\t***Teste instrucao Store half***\n\n");  
    // SH instruction

    funct3 = SH3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2000;           // Destiny addres
    breg[rs2] = 0xABAC;           // value stored
    imm12_s = 2;
    
    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", imm12_s);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de 0x2000: %.8X\n\n", mem[breg[rs1]>>2]);

    printf("\t***Teste instrucao Store word***\n\n");  

    // Sw instruction

    funct3 = SW3;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x2000;           // Destiny addres
    breg[rs2] = 0xABACACAE;       // value stored
    imm12_s = 0;
    
    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm12_s): %.8X\n", imm12_s);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor no endereço de 0x2000: %.8X\n\n", mem[breg[rs1]>>2]);

  // BType instruction
  printf("***Teste instrucao tipo B***\n\n");  
  opcode = BType;

    // BEQ instruction - true condition

    printf("\t***Teste instrucao BEQ***\n\n");  
    funct3 = BEQ3;
    uint32_t previous_pc = 0xC;        // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 3;
    breg[rs2] = 3;
    imm13 = (0x8);                     // always even jumps 

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", imm13);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

    printf("\t***Teste instrucao BEQ(offset negativo)***\n\n");  
    funct3 = BEQ3;
    previous_pc = 0xC;        // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 3;
    breg[rs2] = 3;
    imm13 = 0x1FFE;                          // always even jumps 

    // extend signal 
    imm13 <<= 19;
    imm13 >>= 19;


    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", 0x1FFE);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);


    // BNE instruction - true condition

    printf("\t***Teste instrucao BNE***\n\n");  
    funct3 = BNE3;
    previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 2;
    breg[rs2] = 3;
    imm13 = (0x8);                     // always even jumps 

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", imm13);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

    // BLT instruction - true condition

    printf("\t***Teste instrucao BLT***\n\n");  
    funct3 = BLT3;
    previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0xFFFFFFFF;
    breg[rs2] = 0x00000003;
    imm13 = (0x8);                     // always even jumps 

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", imm13);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

    // BGE instruction - true condition

    printf("\t***Teste instrucao BGE***\n\n");  
    funct3 = BGE3;
    previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x00000003;
    breg[rs2] = 0xFFFFFFFF;
    imm13 = (0x8);                     // always even jumps 

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", imm13);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

    // BLTU instruction - true condition

    printf("\t***Teste instrucao BLTU***\n\n");  
    funct3 = BLTU3;
    previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0x00000003;
    breg[rs2] = 0xFFFFFFFF;
    imm13 = (0x8);                     // always even jumps 

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", imm13);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

    // BGEU instruction - true condition

    printf("\t***Teste instrucao BGEU***\n\n");  
    funct3 = BGEU3;
    previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
    pc = previous_pc;
    rs1 = t0;
    rs2 = t1;
    breg[rs1] = 0xFFFFFFFF;
    breg[rs2] = 0x00000003;
    imm13 = (0x8);                     // always even jumps 

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %X\n", funct3);
    printf("\toffset(imm13): %.8X\n", imm13);
    printf("\tValor no rs1: %.8X\n", breg[rs1]);
    printf("\tValor no rs2: %.8X\n", breg[rs2]);
    printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
    printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

  printf("***Teste instrucao JAL***\n\n");  

  opcode = JAL;
  previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
  pc = previous_pc;
  imm21 = 0x8;
  
  execute();

  printf("\topcode: %d\n", opcode);
  printf("\toffset(imm21): %.8X\n", imm21);
  printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
  printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);


  printf("\t***Teste instrucao JAL(offset negativo)***\n\n");  

  opcode = JAL;
  previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
  pc = previous_pc;
  imm21 = 0x1FFFFE;

  // extend signal 
  imm21 <<= 11;
  imm21 >>= 11;
  
  execute();

  printf("\topcode: %d\n", opcode);
  printf("\toffset(imm21): %.8X\n", 0x1FFFFE);
  printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
  printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

  printf("***Teste instrucao JALR***\n\n");  

  opcode = JALR;
  previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
  pc = previous_pc;
  imm12_i = 0x9;
  rs1 = t0;
  breg[rs1] = 0x2000;
  
  execute();

  printf("\topcode: %d\n", opcode);
  printf("\toffset(imm12_i): %.8X\n", imm12_i);
  printf("\tValor do rs1: %.8X\n", breg[rs1]);
  printf("\tValor do rd: %.8X", breg[rd]);
  printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
  printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

    printf("\t***Teste instrucao JALR(offset negativo)***\n\n");  

  opcode = JALR;
  previous_pc = 0xC;                 // pc is the next instruction(produced in fetch process)
  pc = previous_pc;

  imm12_i = 0xFFF;
  // extend signal 
  imm12_i <<= 20;
  imm12_i >>= 20;

  rs1 = t0;
  breg[rs1] = 0x2004;
  
  execute();

  printf("\topcode: %d\n", opcode);
  printf("\toffset(imm12_i): %.8X\n", 0xFFF);
  printf("\tValor do rs1: %.8X\n", breg[rs1]);
  printf("\tValor do rd: %.8X", breg[rd]);
  printf("\tValor do pc anterior: %.8X\n", previous_pc-4);
  printf("\tValor do pc apos o procedimento: %.8X\n\n", pc);

  // ILAType instruction
  printf("***Teste instrucao ILAType***\n\n");  
  opcode = ILAType;

    // ADDI instruction

    printf("\t***Teste instrucao ADDI***\n\n");  
    funct3 = ADDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x0F;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xF0;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", ADDI3);
    printf("\timm12_i: %.8X\n", 0x0F);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x000000FF);

    printf("\t***Teste instrucao ADDI***\n\n");  
    funct3 = ADDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x8FF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;
    
    breg[rs1] = 0xF0;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x8FF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFFFFF9EF);

    printf("\t***Teste instrucao ADDI(immediato negativo)***\n\n");  
    funct3 = ADDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0xFFF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0xFFF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x0000000E);


    printf("\t***Teste instrucao ADDI(overflow)***\n\n");  
    funct3 = ADDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x001;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0x7FFFFFFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x001);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x80000000);

    printf("\t***Teste 1 instrucao ORI***\n\n");  
    funct3 = ORI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0xFFF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0xFFF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFFFFFFFF);

    printf("\t***Teste 2 instrucao ORI***\n\n");  
    funct3 = ORI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x7FF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x7FF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x000007FF);

    printf("\t***Teste 3 instrucao ORI***\n\n");  
    funct3 = ORI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x800;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x800);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFFFFF800);


    printf("\t***Teste 1 instrucao ANDI***\n\n");  
    funct3 = ANDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0xFFF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xAAAAAAAA;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0xFFF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xAAAAAAAA);

    printf("\t***Teste 2 instrucao ANDI***\n\n");  
    funct3 = ANDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x7FF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xAAAAAAAA;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x7FF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x000002AA);

    printf("\t***Teste 3 instrucao ANDI***\n\n");  
    funct3 = ANDI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x800;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xAAAAAAAA;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x800);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xAAAAA800);


    printf("\t***Teste 1 instrucao XORI***\n\n");  
    funct3 = XORI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0xFFF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xFFFFFFFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0xFFF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0);

    printf("\t***Teste 2 instrucao XORI***\n\n");  
    funct3 = XORI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x7FF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xFFFFFFFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x7FF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFFFFF800);

    printf("\t***Teste 3 instrucao XORI***\n\n");  
    funct3 = XORI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x800;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xFFFFFFFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x800);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x000007FF);

    printf("\t***Teste instrucao SLTI***\n\n");
    breg[rd] = 0;
    funct3 = SLTI3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0x1;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0xFFFFFFFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0x1);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x1);

    printf("\t***Teste instrucao SLTIU***\n\n");  
    breg[rd] = 0;
    funct3 = SLTIU3;
    rd = t1;
    rs1 = t0;

    imm12_i = 0xFFF;
    // extend signal 
    imm12_i <<= 20;
    imm12_i >>= 20;

    breg[rs1] = 0x1;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\timm12_i: %.8X\n", 0xFFF);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x1);

    printf("\t***Teste instrucao SLLI***\n\n");  
    breg[rd] = 0;
    funct3 = SLLI3;
    rd = t1;
    rs1 = t0;

    shamt = 0x3;

    breg[rs1] = 0xFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tshamt: %.8X\n", 0x3);
    printf("\tValor do rs1: %.8X\n", breg[rs1]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x7F8);

    printf("\t***Teste instrucao SRI***\n\n");
      printf("\t\t***Teste instrucao SRLI***\n\n"); 
      breg[rd] = 0;
      funct3 = SRI3;
      funct7 = SRLI7;
      rd = t1;
      rs1 = t0;

      shamt = 0x3;

      breg[rs1] = 0xFF000000;

      execute();

      printf("\topcode: %d\n", opcode);
      printf("\tfunct3: %.8X\n", funct3);
      printf("\tfunct7: %.8X\n", funct7);
      printf("\tshamt: %.8X\n", 0x3);
      printf("\tValor do rs1: %.8X\n", breg[rs1]);
      printf("\tValor do rd: %.8X\n", breg[rd]);
      printf("\tValor esperado do rd: %.8X\n\n", 0x1FE00000);

      printf("\t\t***Teste instrucao SRAI***\n\n"); 
      breg[rd] = 0;
      funct3 = SRI3;
      funct7 = SRAI7;
      rd = t1;
      rs1 = t0;

      shamt = 0x3;

      breg[rs1] = 0xFF000000;

      execute();

      printf("\topcode: %d\n", opcode);
      printf("\tfunct3: %.8X\n", funct3);
      printf("\tfunct7: %.8X\n", funct7);
      printf("\tshamt: %.8X\n", 0x3);
      printf("\tValor do rs1: %.8X\n", breg[rs1]);
      printf("\tValor do rd: %.8X\n", breg[rd]);
      printf("\tValor esperado do rd: %.8X\n\n", 0xFFE00000);

  printf("***Teste instrucao RegType***\n\n");  

    printf("\t***Teste instrucao ADD***\n\n");  
    opcode = RegType;
    funct3 = ADDSUB3;
    funct7 = ADD7;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0xFFFFFFFF;
    breg[rs2] = 0x1;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tfunct7: %.8X\n", funct7);
    printf("\tValor do rs1: %.8X\n", 0xFFFFFFFF);
    printf("\tValor do rs2: %.8X\n", breg[rs2]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0);

    printf("\t***Teste instrucao SUB***\n\n");  
    opcode = RegType;
    funct3 = ADDSUB3;
    funct7 = SUB7;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0xFFFFFFFF;
    breg[rs2] = 0x1;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tfunct7: %.8X\n", funct7);
    printf("\tValor do rs1: %.8X\n", 0xFFFFFFFF);
    printf("\tValor do rs2: %.8X\n", breg[rs2]);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFFFFFFFE);

    printf("\t***Teste instrucao SLL***\n\n");  
    opcode = RegType;
    funct3 = SLL3;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0x000000FF;
    breg[rs2] = 0x8;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tValor do rs1: %.8X\n", 0x000000FF);
    printf("\tValor do rs2: %.8X\n", 0x8);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFF00);

    printf("\t***Teste instrucao SRL***\n\n");  
    opcode = RegType;
    funct3 = SR3;
    funct7 = SRL7;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0xAB000000;
    breg[rs2] = 0x8;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tfunct7: %.8X\n", funct7);
    printf("\tValor do rs1: %.8X\n", 0xAB000000);
    printf("\tValor do rs2: %.8X\n", 0x8);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x00AB0000);

    printf("\t***Teste instrucao SRA***\n\n");  
    opcode = RegType;
    funct3 = SR3;
    funct7 = SRA7;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0xAB000000;
    breg[rs2] = 0x8;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tfunct7: %.8X\n", funct7);
    printf("\tValor do rs1: %.8X\n", 0xAB000000);
    printf("\tValor do rs2: %.8X\n", 0x8);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xFFAB0000);

    printf("\t***Teste instrucao SLT***\n\n");  
    opcode = RegType;
    funct3 = SLT3;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0xFFFFFFFF;
    breg[rs2] = 0x1;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tValor do rs1: %.8X\n", 0xFFFFFFFF);
    printf("\tValor do rs2: %.8X\n", 0x1);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x1);

    printf("\t***Teste instrucao SLTU***\n\n");  
    opcode = RegType;
    funct3 = SLTU3;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0x1;
    breg[rs2] = 0xFFFFFFFF;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tValor do rs1: %.8X\n", 0x1);
    printf("\tValor do rs2: %.8X\n", 0xFFFFFFFF);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x1);

    printf("\t***Teste instrucao XOR***\n\n");  
    opcode = RegType;
    funct3 = XOR3;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0x0F0F0F0F;
    breg[rs2] = 0xFEFDFCFB;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tValor do rs1: %.8X\n", 0x0F0F0F0F);
    printf("\tValor do rs2: %.8X\n", 0xFEFDFCFB);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xF1F2F3F4);

    printf("\t***Teste instrucao OR***\n\n");  
    opcode = RegType;
    funct3 = OR3;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0xAAA00AAA;
    breg[rs2] = 0x11111111;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tValor do rs1: %.8X\n", 0xAAA00AAA);
    printf("\tValor do rs2: %.8X\n", 0x111FF111);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0xBBBFFBBB);

    printf("\t***Teste instrucao AND***\n\n");  
    opcode = RegType;
    funct3 = AND3;

    rs1 = t4;
    rs2 = t5;
    rd = t4;

    breg[rs1] = 0x1234ABCD;
    breg[rs2] = 0xEFEFFEFE;

    execute();

    printf("\topcode: %d\n", opcode);
    printf("\tfunct3: %.8X\n", funct3);
    printf("\tValor do rs1: %.8X\n", 0x1234ABCD);
    printf("\tValor do rs2: %.8X\n", 0x00800808);
    printf("\tValor do rd: %.8X\n", breg[rd]);
    printf("\tValor esperado do rd: %.8X\n\n", 0x0224AACC);

  printf("***Teste instrucao ECALL***\n\n");
    printf("\t***Teste comando PrintSring***\n\n");

    opcode   = ECALL;
    breg[a7] = SYS_PRINT_STRING;
    breg[a0] = 0x2000;

    mem[DATA]   = 0x6f20734f;		// Os o
    mem[DATA+1] = 0x206f7469;		// ito 
    mem[DATA+2] = 0x6d697270;		// prim
    mem[DATA+3] = 0x6f726965;		// eiro
    mem[DATA+4] = 0x756e2073;		// s nu
    mem[DATA+5] = 0x6f72656d;		// mero
    mem[DATA+6] = 0x72702073;		// s pr
    mem[DATA+7] = 0x736f6d69;		// imos
    mem[DATA+8] = 0x6f617320;		//  sao
    mem[DATA+9] = 0x00203a20;		//  : 

    execute();

    printf("\n\n");

    printf("\t***Teste comando PrintChar***\n\n");

    opcode   = ECALL;
    breg[a7] = SYS_PRINT_CHAR;
    breg[a0] = 'A';

    execute();

    printf("\n\n");

    printf("\t***Teste comando PrintInt***\n\n");

    mem[DATA]   = 0x00000007;
    opcode   = ECALL;
    breg[a7] = SYS_PRINT_INT;
    breg[a0] = 7;

    execute();

    printf("\n\n");

    printf("\t***Teste comando EXIT***\n\n");

    mem[DATA]   = 0x00000007;
    opcode   = ECALL;
    breg[a7] = SYS_EXIT;

    execute();

    printf("Nao deve ser printado essa mensagem");
  

  return 0;
}
