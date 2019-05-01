#include "./include/fec.h"
#include "./include/RISCV_mem.h"

int32_t opcode=0;
int32_t rs1=0;
int32_t rs2=0;
int32_t rt=0;
int32_t rd=0;
int32_t shamt=0;
int32_t funct3=0;
int32_t funct7=0;
int32_t imm12_i=0;
int32_t imm12_s=0;
int32_t imm13=0;
int32_t imm20_u=0;
int32_t imm21=0;

uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000;

enum BREG{
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
};

enum OPCODES {                        // lembrem que so sao considerados os 7 primeiros bits dessas constantes
  LUI = 0x37,     AUIPC = 0x17,       // atribui 20 bits mais significativos
  ILType = 0x03,                      // Load type
  BType = 0x63,                       // branch condicional
  JAL = 0x6F,     JALR = 0x67,        // jumps - JAL formato UJ, JALR formato I
  StoreType = 0x23,                   // store
  ILAType = 0x13,                     // logico-aritmeticas com imediato
  RegType = 0x33,                     // operacoes LA com registradores
  ECALL = 0x73                        // chamada do sistema - formato I
};

enum FUNCT3 {                                                       //campo auxiliar de 3 bits
  BEQ3=0, BNE3=01, BLT3=04, BGE3=05, BLTU3=0x06, BGEU3=07,          //branches
  LB3=0, LH3=01, LW3=02, LBU3=04, LHU3=05,                          //loads
  SB3=0, SH3=01, SW3=02,                                            //stores
  ADDSUB3=0, SLL3=01, SLT3=02, SLTU3=03,                            //LA com
  XOR3=04, SR3=05,                                                  //registradores
  OR3=06, AND3=07, ADDI3=0, ORI3=06, SLTI3=02, XORI3=04, ANDI3=07,  //LA com
  SLTIU3=03, SLLI3=01, SRI3=05                                      //imediatos
};

enum FUNCT7 {
  // campo auxiliar de 7 bits para as instrucoes SRLI/SRAI, ADD/SUB, SRL/SRA
  ADD7=0, SUB7=0x20, SRA7=0x20, SRL7=0, SRLI7=0x00, SRAI7=0x20
};


void read_bin()
{
  FILE *fptr;

  // .text area (0x00000000)
  int i=0;
  int32_t hex_number=0;

  // Read text.bin file and transfers to mem area
  if ((fptr = fopen("./text.bin","rb")) == NULL){
      printf("Error! opening file\n");

      // Program exits if the file pointer returns NULL.
      exit(1);
  }


  while(!feof(fptr))
  {
    fread(&hex_number, 4, 1, fptr);

    // Do not read anymore after reach end of file
    if(feof(fptr)){
      break;
    }

    mem[i++] = hex_number;
  }

  fclose(fptr); 

  // .data area(0x00002000) - each index corresponds to 4 bytes
  i = DATA;

  // Read data.bin file and transfers to mem area
  if ((fptr = fopen("./data.bin","rb")) == NULL){
      printf("Error! opening file\n");

      // Program exits if the file pointer returns NULL.
      exit(1);
  }

  // Fills while fit in memory
  while(i != MEM_SIZE || !feof(fptr))
  {
    fread(&hex_number, 4, 1, fptr);

    // Do not read anymore after reach end of file
    if(feof(fptr)){
      break;
    }

    mem[i++] = hex_number;
  }

  fclose(fptr); 
}

void fetch()
{
  ri = mem[pc>>2];
  pc += 4;
}

void decode()
{
  uint32_t opcode_mask = 0x0000007F; 
  uint32_t rd_mask = 0x0000F80; 
  uint32_t funct3_mask = 0x00007000; 
  uint32_t rs1_mask = 0x000F8000; 
  uint32_t shamt_mask = 0x01F00000;
  uint32_t rs2_mask = 0x01F00000; 
  uint32_t funct7_mask = 0xFE000000;
  uint32_t imm12_i_mask = 0xFFF00000;
  uint32_t imm12_s_mask_0_4 = 0x00000F80;
  uint32_t imm12_s_mask_5_11 = 0xFE000000;
  uint32_t imm13_mask_11_1_4 = 0x00000F80;
  uint32_t imm13_mask_5_12 = 0xFE000000;
  uint32_t imm20_u_mask = 0xFFFFF000;
  uint32_t imm21_mask = 0xFFFFF000;

  int32_t imm12_s_5_11 = 0;
  int32_t imm13_5_12 = 0;

  // opcode
  opcode = ri&opcode_mask;

  // rd
  rd = ri&rd_mask;
  rd >>= 7;

  // funct3
  funct3 = ri&funct3_mask;
  funct3 >>= 12; 

  // rs1
  rs1 = ri&rs1_mask;
  rs1 >>= 15;

  // rs2
  rs2 = ri&rs2_mask;
  rs2 >>= 20;

  // shamt
  shamt = ri&shamt_mask;
  shamt >>= 20;

  // funct7
  funct7 = ri&funct7_mask;
  funct7 >>= 25;

  // imm12_i
  imm12_i = ri&imm12_i_mask;
  imm12_i >>= 20;

  // imm12_s
  imm12_s = ri&imm12_s_mask_0_4;
  imm12_s >>= 7;

  imm12_s_5_11 = ri&imm12_s_mask_5_11;
  imm12_s_5_11 >>= 20;

  imm12_s |= imm12_s_5_11;

  // imm12_s
  imm12_s = ri&imm12_s_mask_0_4;
  imm12_s >>= 7;

  imm12_s_5_11 = ri&imm12_s_mask_5_11;
  imm12_s_5_11 >>= 20;

  imm12_s |= imm12_s_5_11;

  // imm13
  imm13 = 0;
  imm13 = ri&imm13_mask_11_1_4;
  imm13 >>= 6;

  imm13_5_12 = ri&imm13_mask_5_12;
  imm13_5_12 >>= 19;

  imm13 |= imm13_5_12;

  // imm20_u
  imm20_u = ri&imm20_u_mask;
  imm20_u >>= 12;

  // imm21
  imm21 = ri&imm21_mask;
  imm21 >>= 12;

}

void execute()
{
  switch(opcode){
  case LUI:
  case AUIPC:
  case ILType:
    switch (funct3){
    case LB3:
    case LH3:
    case LW3:
    case LBU3:
    case LHU3:
      break;
    }
  case BType:
    switch (funct3){
    case BEQ3:
    case BNE3:
    case BLT3:
    case BGE3:
    case BLTU3:
    case BGEU3:
      break;
    }
  case JAL:
  case JALR:
  case StoreType:
    switch (funct3){
    case SB3:
    case SH3:
    case SW3:
      break;
    }
  case ILAType:
    switch (funct3){        
    case ADDI3:
    case ORI3:
    case SLTI3:
    case XORI3:
    case ANDI3:
    case SLTIU3:
    case SLLI3:
    case SRI3:
      switch (funct7){
      case SRLI7:
      case SRAI7:
        break;
      }
    }
  case RegType:
    switch (funct3){
      case ADDSUB3:
        switch (funct7){
          case ADD7:
          case SUB7:
            break;
        }
      case SLL3:
      case SLT3:
      case SLTU3:
      case XOR3:
      case SR3:
        switch (funct7){
          case SRL7:
          case SRA7:
            break;
        }
      case OR3:
      case AND3:
        break;
    }
  case ECALL:
    break;
  }
}

