#include <stdio.h>
#include <stdint.h>
#include "RISCV_mem.h"

// This code is a TDD process result.
// That's the reason that every function has it's own test
// based in the RISCV_mem.h order, except stores function. The following tests
// is not equal as the recomended, but is based on,
// as verified below.

// The compiler set is specified in Makefile file.

int main(int argc, char* argv[])
{
  uint32_t u32 = 0;
  uint16_t u16 = 0;
  uint8_t u8 = 0;

  int32_t s32 = 0;
  int16_t s16 = 0;
  int8_t s8 = 0;

  // -------------------------------------    Store word test     --------------------------------
  printf("\t*** Store word test ***\n\n");
  // Save word values(32bits)
  sw(0,0,0x100000FF);
  sw(4,0,0x0000CAFE);
  printf("Memory values:\t%#.8X\n", mem[0]);
  printf("Memory values:\t%#.8X\n\n", mem[1]);

  // -------------------------------------    Load word test     --------------------------------

  printf("\t*** Load word test ***\n\n");
  // Trivial case
  u32 = lw(0,0);
  printf("First load:\t%#.8X\t%d\n", u32, u32);

  // Error case - not aligned address
  u32 = lw(3,0);
  printf("Error case:\t%#.8X\n", u32);

  // 2th word value
  u32 = lw(4,0);
  printf("2th word:\t%#.8X\t%d\n", u32, u32);

  // Error case - access offset out of word range
  u32 = lw(4,7);
  printf("2th word:\t%#.8X\t%d\n", u32, u32);

  // -------------------------------------    Store halfword test     --------------------------------

  printf("\t*** Store half word test ***\n\n");
  // Save half word
  sh(8,0,0x00FE);
  printf("Half word:\t%#.8X\n", mem[2]);

  // Save at the 2th offset
  sh(8,2,0xAAFF);
  printf("Half word:\t%#.8X\n", mem[2]);  

  // Overwrite at the 2th offset
  sh(8,2,0xCAFE);
  printf("Overwrite:\t%#.8X\n", mem[2]);  

  // Error case - address access out of half word range
  sh(9,0,0xCAFE);
  printf("Error case:\t%#.8X\n", mem[2]);  

  // Error case - access offset out of half word range
  sh(8,3,0xCAFE);
  printf("Error case:\t%#.8X\n\n", mem[2]);  

  // -------------------------------------    Store byte test     --------------------------------

  printf("\t*** Store byte test ***\n\n");
  // Save byte
  sb(12,0,0xFE);
  printf("1th byte:\t%#.8X\n", mem[3]);

  // Save byte at 1th offset
  sb(12,1,0xCA);
  printf("2th byte:\t%#.8X\n", mem[3]);

  // Save byte at 2th offset
  sb(12,2,0xBB);
  printf("3th byte:\t%#.8X\n", mem[3]);

  // Save byte at 3th offset
  sb(12,3,0xAA);
  printf("4th byte:\t%#.8X\n", mem[3]);

  // Overwrite byte at beginning
  sb(12,0,0xAA);
  printf("Overwrite:\t%#.8X\n", mem[3]);

  // Overwrite byte at 1th offset
  sb(12,1,0xBB);
  printf("Overwrite:\t%#.8X\n", mem[3]);

  // Overwrite byte at 2th offset
  sb(12,2,0xCC);
  printf("Overwrite:\t%#.8X\n", mem[3]);

  // Overwrite byte at 3th offset
  sb(12,3,0xDD);
  printf("Overwrite:\t%#.8X\n", mem[3]);

  printf("\t*** Next word memory ***\n");

  // Save byte
  sb(16,0,0x04);
  printf("1th byte:\t%#.8X\n", mem[4]);

  // Save byte at 1th offset
  sb(16,1,0x03);
  printf("2th byte:\t%#.8X\n", mem[4]);

  // Save byte at 2th offset
  sb(16,2,0x02);
  printf("3th byte:\t%#.8X\n", mem[4]);

  // Save byte at 3th offset
  sb(16,3,0x01);
  printf("4th byte:\t%#.8X\n", mem[4]);

  // -------------------------------------    Load half word(signed)     --------------------------------

  printf("\t*** Load half word(signed) ***\n\n");
  // Save word
  sw(20,0,0x1111CAFE);
  printf("Memory value:\t%#.4X\n", mem[5]);

  // Select 1th half word
  s16 = lh(20,0);

  // The conversion is for printing 4 digits(by default, C prints all digit)
  // in signed values
  u16 = (unsigned) s16;
  printf("1th half signed:\t%#.4X\t%d\n",u16, s16);

  // Select 2th half word
  s16 = lh(20,2);
  printf("2th half signed:\t%#.4X\t%d\n", s16, s16);

  // Error case - address access out of word range 
  s16 = lh(21,0);
  printf("Error case:\t%#.4X\n", s16);

  // Error case - address access out of half word range 
  s16 = lh(20,1);
  printf("Error case:\t%#.4X\n\n", s16);

  // -------------------------------------    Load half word(unsigned)     --------------------------------
  printf("\t*** Load half word(unsigned) ***\n\n");
  // Word
  printf("Memory value:\t%#.4X\n", mem[5]);

  // Select 1th half word
  u16 = lhu(20,0);
  printf("1th half unsigned:\t%#.4X\t%d\n", u16, u16);

  // Select 2th half word
  u16 = lhu(20,2);
  printf("2th half unsigned:\t%#.4X\t%d\n", u16, u16);

  // Error case - address access out of word range 
  u16 = lhu(25,0);
  printf("Error case:\t%#.4X\n", u16);

  // Error case - address access out of half word range 
  u16 = lhu(20,1);
  printf("Error case:\t%#.4X\n\n", u16);

  // -------------------------------------    Load byte(signed)     --------------------------------
  printf("\t*** Load byte(signed) ***\n\n");
  // Save word
  sw(24,0,0x04030201);
  sw(28,0,0x7711CAFE);
  printf("Memory value:\t%#.8X\t\n", mem[6]);

    // Select 1th byte
  s8 = lb(24,0);
  u8 = (unsigned) s8;
  printf("1th byte signed:\t%#.2X\t%d\n", u8, s8);

  // Select 2th byte
  s8 = lb(24,1);
  u8 = (unsigned) s8;
  printf("2th byte signed:\t%#.2X\t%d\n", u8, s8);

  // Select 3th half word
  s8 = lb(24,2);
  printf("3th byte signed:\t%#.2X\t%d\n", s8, s8);

  // Select 4th half word
  s8 = lb(24,3);
  printf("4th byte signed:\t%#.2X\t%d\n", s8, s8);

  printf("\t*** Next word memory ***\n");

  printf("Memory value:\t%#.8X\n", mem[7]);

  // Select 1th byte
  s8 = lb(28,0);
  u8 = (unsigned) s8;
  printf("1th byte signed:\t%#.2X\t%d\n", u8, s8);

  // Select 2th byte
  s8 = lb(28,1);
  u8 = (unsigned) s8;
  printf("2th byte signed:\t%#.2X\t%d\n", u8, s8);

  // Select 3th half word
  s8 = lb(28,2);
  printf("3th byte signed:\t%#.2X\t%d\n", s8, s8);

  // Select 4th half word
  s8 = lb(28,3);
  printf("4th byte signed:\t%#.2X\t%d\n", s8, s8);

  // -------------------------------------    Load byte(unsigned)     --------------------------------
  printf("\t*** Load byte(unsigned) ***\n\n");
  // Word
  printf("Memory value:\t%#.2X\n", mem[7]);

  // Select 1th byte
  u8 = lbu(28,0);
  printf("1th byte unsigned:\t%#.2X\t%d\n", u8, u8);

  // Select 2th byte
  u8 = lbu(28,1);
  printf("2th byte unsigned:\t%#.2X\t%d\n", u8, u8);

  // Select 3th half word
  u8 = lbu(28,2);
  printf("3th byte unsigned:\t%#.2X\t%d\n", u8, u8);

  // Select 4th half word
  u8 = lbu(28,3);
  printf("4th byte unsigned:\t%#.2X\t%d\n", u8, u8);

  // Error case - address access out of word range 
  u8 = lbu(29,0);
  printf("Error case:\t%#.2X\n", u8);

  // Error case - address access out of byte range 
  u8 = lbu(28,4);
  printf("Error case:\t%#.2X\n\n", u8);

  printf("\t*** Dump mem ***\n\n");

  // Prints memory data
  dump_mem(0,8);

  return 0;

}
