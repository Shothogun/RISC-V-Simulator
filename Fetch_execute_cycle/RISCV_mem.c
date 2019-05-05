#include "./include/RISCV_mem.h"
#include "./include/fec.h"

int32_t mem[MEM_SIZE];

// Breg initialization(sp = 0x00003FFC, gp = 0x00001800)
int32_t breg[32] = {0,0,0x00003FFC,0x00001800,0,0,0,0,
                    0,0,0         ,0         ,0,0,0,0,
                    0,0,0         ,0         ,0,0,0,0,
                    0,0,0         ,0         ,0,0,0,0,};

int32_t lw(uint32_t  address, int32_t byte_offset)
{
  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if((byte_offset >= 4) |( byte_offset <= -4)){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  return mem[address>>2];
}

int32_t lh(uint32_t  address, int32_t byte_offset)
{

  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if(byte_offset >= 4  | byte_offset <= -4){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  int32_t selected_half_word = 0;
  int16_t return_value = 0;

  // Copies mem value
  selected_half_word = mem[address>>2];

  // Selects the chosen offset half word bits
  selected_half_word >>= (byte_offset*8);

  // Gets it's value as a signed half word
  return_value = selected_half_word;

  return return_value;
}

int32_t lhu(uint32_t  address, int32_t byte_offset)
{
  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if(byte_offset >= 4  | byte_offset <= -4){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  int32_t select_half_word= 0;
  uint16_t return_value = 0;

  // Copies mem value
  select_half_word = mem[address>>2];

  // Selects the chosen offset half word bits
  select_half_word >>= (byte_offset*8);


  // Gets it's value as a unsigned half word
  return_value = select_half_word;

  return return_value;
}

int32_t lb(uint32_t  address, int32_t byte_offset)
{

  int32_t select_byte = 0;
  int8_t return_value = 0; 

  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if(byte_offset >= 4  | byte_offset <= -4){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  // Copies mem value
  select_byte = mem[address>>2];

  // Selects the chosen offset byte bits
  select_byte >>= (byte_offset*8);

  // Gets it's value as a signed byte
  return_value = select_byte;

  return return_value;
}

int32_t lbu(uint32_t  address, int32_t byte_offset)
{
  int32_t select_byte = 0;
  uint8_t return_value = 0;
  
  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if((byte_offset >= 4) |( byte_offset <= -4)){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  // Copies mem value
  select_byte = mem[address>>2];

  // Selects the chosen offset byte bits
  select_byte >>= (byte_offset*8);

  // Gets it's value as a unsigned half word
  return_value = select_byte;

  return return_value;
}

void sw(uint32_t  address, int32_t byte_offset, int32_t data)
{

  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if((byte_offset >= 4) |( byte_offset <= -4)){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  // Access corresponding memory word address(each element is 4 bytes)
  mem[address>>2] = data;
}

void sh(uint32_t  address, int32_t byte_offset, int16_t data)
{
  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if((byte_offset >= 4) |( byte_offset <= -4)){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  int32_t tmp = data;
  tmp <<= (byte_offset*8);
  
  // Overwrite mask
  uint32_t mask = 0xFFFF;
  mask = ~(mask<<(byte_offset*8));

  // Clear the chosen half word range
  mem[address>>2] &= mask;

  // Overwrite memory half word address
  mem[address>>2] |= tmp;
}

void sb(uint32_t  address, int32_t byte_offset, int8_t data)
{
  int32_t tmp = data;

  // If address is not multiple of 4,
  // converts it's module to byte-offset
  if(address%4 != 0){
    byte_offset += address%4;
    address -= address%4;
  }

  // If byte-offset is greater than 4,
  // adds it to address
  if((byte_offset >= 4) |( byte_offset <= -4)){
    address += 4*(byte_offset/4);
    byte_offset = byte_offset%4;
  }

  // Eliminates sign bit propagation
  tmp &= 0xFF;
  tmp <<= (byte_offset*8);
  
  // Overwrite mask
  uint32_t mask = 0x000000FF;
  mask = ~(mask<<(byte_offset*8));

  // Clear the chosen byte range
  mem[address>>2] &= mask;

  // Overwrite memory half word address
  mem[address>>2] |= tmp;
}

void dump_mem(int start, int end, char format)
{
  int pos = start>>2;
  int endline = end>>2;

  switch (format)
  {
  case 'h':
    for (int i=pos; i < endline; i++){
      printf("mem[%03d]\t =\t %.8X\n", i, mem[i]);
    }
    break;
  
  case 'd':
    for (int i=pos; i < endline; i++){
      printf("mem[%03d]\t =\t %d\n", i, mem[i]);
    }
    break;
  }

}
