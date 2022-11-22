#include "cpu/mmu.h" 
#include "memory/dram.h"
#include "memory/instruction.h"

uint64_t va2pa(uint64_t vaddr) 
{
    return vaddr%MM_LEN;
}