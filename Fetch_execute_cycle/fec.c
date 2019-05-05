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
  int32_t opcode_mask = 0x0000007F; 
  int32_t rd_mask = 0x0000F80; 
  int32_t funct3_mask = 0x00007000; 
  int32_t rs1_mask = 0x000F8000; 
  int32_t shamt_mask = 0x01F00000;
  int32_t rs2_mask = 0x01F00000; 
  int32_t funct7_mask = 0xFE000000;

  int32_t imm12_i_mask = 0xFFF00000;
  int32_t imm12_s_mask_0_4 = 0x00000F80;
  int32_t imm12_s_mask_5_11 = 0xFE000000;
  int32_t imm12_s_5_11 = 0;

  int32_t imm13_mask_11_1_4 = 0x00000F80;
  int32_t imm13_mask_5_12 = 0xFE000000;
  int32_t imm13_mask_11 = 0x00000080;
  int32_t imm13_mask_12 = 0x80000000;
  int32_t imm13_5_12 = 0;
  int32_t imm13_11 = 0;
  int32_t imm13_12 = 0;

  int32_t imm20_u_mask = 0xFFFFF000;

  int32_t imm21_11 = 0;
  int32_t imm21_12_19 = 0;
  int32_t imm21_20 = 0;
  int32_t imm21_mask_1_10 = 0x7FE00000;
  int32_t imm21_mask_11 = 0x00100000;
  int32_t imm21_mask_12_19 = 0x000FF000;
  int32_t imm21_mask_20 = 0x80000000;


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

    // extend signal 

    imm12_i <<= 20;
    imm12_i >>= 20;

  // imm12_s
  imm12_s = ri&imm12_s_mask_0_4;
  imm12_s >>= 7;

  imm12_s_5_11 = ri&imm12_s_mask_5_11;
  imm12_s_5_11 >>= 20;

  imm12_s |= imm12_s_5_11;

    // extend signal 

    imm12_s <<= 20;
    imm12_s >>= 20;

  // imm13
  imm13 = ri&imm13_mask_11_1_4;

  // Gets and position bit 11 and 12
  imm13_11 = (ri&imm13_mask_11)<<4;
  imm13_12 = (ri&imm13_mask_12)>>19;

  // Erases garbage bit 11
  imm13 &= ~imm13_mask_11;
  
  imm13 >>= 7;

  imm13_5_12 = ri&imm13_mask_5_12;

  // Erases garbage bit 12
  imm13_5_12 &= ~imm13_mask_12;

  imm13_5_12 = imm13_5_12>>20;

  imm13 |= imm13_5_12;
  imm13 |= imm13_11;
  imm13 |= imm13_12;

  imm13 &= ~(0x1);

    // extend signal 

    imm13 <<= 19;
    imm13 >>= 19;

  // imm20_u
  imm20_u = ri&imm20_u_mask;
  imm20_u >>= 12;

    // extend signal 

    imm20_u <<= 12;
    imm20_u >>= 12;


  // imm21
  imm21 = (ri&imm21_mask_1_10)>>20;
  imm21_11 = (ri&imm21_mask_11)>>9;
  imm21_12_19 = ri&imm21_mask_12_19;
  imm21_20 = (ri&imm21_mask_20)>>11;

  imm21 |= imm21_11;
  imm21 |= imm21_12_19;
  imm21 |= imm21_20;

  imm21 &= ~(0x1);


    // extend signal 

    imm21 <<= 11;
    imm21 >>= 11;

}

void execute()
{
  int i=0;
  int number=0;
  char character;
  uint32_t urs1,urs2, uimm12_i;
  switch(opcode)
  {
  case LUI:
    breg[rd] = (imm20_u<<12);
    breg[rd] &= ~(0xFFF);
    break;
  case AUIPC:
    pc -= 4;
    breg[rd] = pc + (imm20_u<<12);
    pc += 4;
    break;
  case ILType:
    switch (funct3)
    {
    case LB3:
      breg[rd] = lb(breg[rs1], imm12_i);
      break;
    case LH3:
      breg[rd] = lh(breg[rs1], imm12_i);
      break;
    case LW3:
      breg[rd] = lw(breg[rs1], imm12_i);
      break;
    case LBU3:
      breg[rd] = lbu(breg[rs1], imm12_i);
      break;
    case LHU3:
      breg[rd] = lhu(breg[rs1], imm12_i);
      break;
    }
    break;
  case BType:
    switch (funct3)
    {
    case BEQ3:
      pc -= 4;
      if(breg[rs1] == breg[rs2]){
        pc += imm13;
      }
      else{
        pc += 4;
      }
      break;
    case BNE3:
      pc -= 4;
      if(breg[rs1] != breg[rs2]) {
        pc += imm13;
      }
      else{
        pc += 4;
      }
      break;
    case BLT3:
      pc -= 4;
      if(breg[rs1] < breg[rs2]){
         pc += imm13;
      }
      else{
        pc += 4;
      }
      break;
    case BGE3:
      pc -= 4;
      if(breg[rs1] > breg[rs2]){
         pc += imm13;
      }

      else{
        pc += 4;
      }

      break;
    case BLTU3:
      pc -= 4;
      urs1 = (uint32_t) breg[rs1];
      urs2 = (uint32_t) breg[rs2];
      if(urs1 < urs2){ 
        pc += imm13;
      }
      else{
        pc += 4;
      }
      break;
    case BGEU3:
      pc -= 4;
      urs1 = (uint32_t) breg[rs1];
      urs2 = (uint32_t) breg[rs2];
      if(urs1 > urs2){
        pc += imm13;
      }

      else{
        pc += 4;
      }
      break;
    }
    break;
  case JAL:
    pc -= 4;
    breg[rd] = pc+4;
    pc += imm21;
    break;
  case JALR:
    pc -= 4;
    breg[rd] = pc+4;
    pc = (breg[rs1]+imm12_i)&~(0x1);
    break;
  case StoreType:
    switch (funct3)
    {
    case SB3:
      sb(breg[rs1], imm12_s, breg[rs2]);
      break;
    case SH3:
      sh(breg[rs1], imm12_s, breg[rs2]);
      break;
    case SW3:
      sw(breg[rs1], imm12_s, breg[rs2]);
      break;
    }
    break;
  case ILAType:
    switch (funct3)
    {        
    case ADDI3:
      breg[rd] = breg[rs1] + imm12_i;
      break;
    case ORI3:
      breg[rd] = breg[rs1]|imm12_i;
      break;
    case SLTI3:
      if(breg[rs1] < imm12_i) breg[rd] = 0x1;
      break;
    case XORI3:
      breg[rd] = breg[rs1]^imm12_i;
      break;
    case ANDI3:
      breg[rd] = breg[rs1]&imm12_i;
      break;
    case SLTIU3:
      uimm12_i = (uint32_t) imm12_i;
      urs1 = (uint32_t) breg[rs1];
      if(urs1 < uimm12_i) breg[rd] = 0x1;
      break;
    case SLLI3:
      breg[rd] = breg[rs1]<<shamt;
      break;
    case SRI3:
      switch (funct7)
      {
      case SRLI7:
        breg[rd] = (uint32_t) breg[rs1]>>shamt;
        break;
      case SRAI7:
        breg[rd] = breg[rs1]>>shamt;
        break;
      }
      break;
    }
    break;
  case RegType:
    switch (funct3)
    {
    case ADDSUB3:
      switch (funct7)
      {
        case ADD7:
          breg[rd] = breg[rs1] + breg[rs2];
          break;
        case SUB7:
          breg[rd] = breg[rs1] - breg[rs2];
          break;
      }
      break;
    case SLL3:
      breg[rd] = breg[rs1]<<(0x1F&breg[rs2]);
      break;
    case SLT3:
      if(breg[rs1] < breg[rs2]) breg[rd] = 0x1;
      break;
    case SLTU3:
      urs1 = (uint32_t) breg[rs1];
      urs2 = (uint32_t) breg[rs2];
      if(urs1 < urs2) breg[rd] = 0x1;
      break;
    case XOR3:
      breg[rd] = breg[rs1]^breg[rs2];
      break;
    case SR3:
      switch (funct7)
      {
        case SRL7:
          breg[rd] = (uint32_t) breg[rs1]>>(0x1F&breg[rs2]);
          break;
        case SRA7:
          breg[rd] = breg[rs1]>>(0x1F&breg[rs2]);
          break;
      }
      break;
    case OR3:
      breg[rd] = breg[rs1] | breg[rs2];
      break;
    case AND3:
      breg[rd] = breg[rs1] & breg[rs2];
      break;
    }
    break;
  case ECALL:
    switch (breg[a7])
    {
    case SYS_PRINT_INT:
      number = breg[a0];
      printf("%d", number);
      break;

    case SYS_PRINT_STRING:
      character = lbu(breg[a0],i);
      while(character){
        printf("%c", character);
        i++;
        character = lbu(breg[a0],i);
      }
      break;
    case SYS_PRINT_CHAR:
      character = breg[a0];
      printf("%c", character);
      break;

    case SYS_EXIT:
      printf("\n-- program is finished running --\n");
      exit(1);
      break;
    }
    break;
  }
}

void step(){
  fetch();
  decode();
  execute();
  breg[zero] = 0;                 // zero is always 0 = hardwired 
}

void run(){
  while(1){
    step();
    if(pc == 0x2000){
      printf("-- program is finished running (dropped off bottom) --!\n");
      exit(0);
    } 
  }
}

void dump_reg(char format){
  switch (format)
  {
  case 'd':
    for(int i = 0; i < 32; i++){
      printf("x%d: %d\n", i, breg[i]);
    }
    printf("pc: %d\n", pc);
    printf("pc : %d\n", ri);
    break;
  
  case 'h':
    for(int i = 0; i < 32; i++){
      printf("x%02d: %.8X\n", i, breg[i]);
    }
    printf("pc : %.8X\n", pc-4);
    printf("ri : %.8X\n", ri);
    break;
  }
}
