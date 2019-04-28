#ifndef RISCV_MEM_H
#define RISCV_MEM_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// RISCV simulator memory size(16KBytes)
#define  MEM_SIZE  4096

// Memory set, exported to differents files
extern int32_t mem[MEM_SIZE];

int32_t lw(uint32_t  address, int32_t byte_offset);
int32_t lh(uint32_t  address, int32_t byte_offset);
int32_t lhu(uint32_t  address, int32_t byte_offset);
int32_t lb(uint32_t  address, int32_t byte_offset);
int32_t lbu(uint32_t  address, int32_t byte_offset);
void sw(uint32_t  address, int32_t byte_offset, int32_t data);
void sh(uint32_t  address, int32_t byte_offset, int16_t data);
void sb(uint32_t  address, int32_t byte_offset, int8_t data);
void dump_mem(uint32_t address, uint32_t wsize);

#endif