#include "./include/fec.h"
#include "./include/RISCV_mem.h"

uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000;
uint32_t sp = 0x00003FFC;
uint32_t gp = 0x00001800;

void read_bin()
{
  FILE *fptr;
  int n=0;
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


