#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "cpu/register.h"
#include "memory/dram.h"

static uint64_t decode(od_t od) 
{
    if(od.type == IMM) 
    {
        return *(uint64_t *)&od.imm;
    }
    else if(od.type == REG)
    {
        return (uint64_t)od.reg1;
    }
    else 
    {
        uint64_t vaddr = 0;
        if(od.type == MM_IMM)
        {
            vaddr = od.imm;
        }
        else if(od.type == MM_REG)
        {
            vaddr = *(od.reg1);
        }
        else if(od.type == MM_IMM_REG)
        {
            vaddr = *(od.reg1) + od.imm;
        }
        else if(od.type ==  MM_REG1_REG2)
        {
            vaddr = *(od.reg1) + od.imm ;
        }
        else if(od.type == MM_IMM_REG1_REG2)
        {
            vaddr = od.imm + *(od.reg1) +*(od.reg2);
        }
        else if(od.type == MM_REG2_S)
        {
            vaddr = (*(od.reg2)) * od.scal;
        }
        else if(od.type == MM_IMM_REG2_S)
        {
            vaddr = od.imm + (*(od.reg2)) * od.scal;
        }
        else if(od.type == MM_REG1_REG2_S)
        {
            vaddr =  *(od.reg1)+(*(od.reg2)) * od.scal;
        }
        else if(od.type == MM_IMM_REG1_REG2_S)
        {
            vaddr = od.imm+*(od.reg1)+(*(od.reg2)) * od.scal;
        }
        return vaddr;
    }
}

void instruction_cycle() 
{
    inst_t *instr = (inst_t *)reg.rip;
    //imm: imm
    //reg: value
    //mm: paddr
    uint64_t src = decode(instr->src);
    uint64_t dst = decode(instr->dst);
    handler_t handler = handler_table[instr->op];
    handler(src, dst);
    printf("%s\n", instr->code);
}
void init_handler_table()
{
    handler_table[mov_reg_reg] = &move_reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler; 
    handler_table[call] = &call_handler;
    handler_table[push_reg] = &push_reg_handler;
    handler_table[mov_reg_mem] = &move_reg_mem_handler;
    handler_table[mov_mem_reg] = &move_mem_reg_handler;
    handler_table[pop_reg] = &pop_reg_handler;
    handler_table[retq] = &retq_handler;
}

void move_reg_reg_handler(uint64_t src, uint64_t dst)
{
    //src: reg
    //dst: reg
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}

void move_mem_reg_handler(uint64_t src, uint64_t dst)
{
    //src: mem
    //dst: reg
    *(uint64_t *)dst = read64bits_dram(va2pa(src));
    reg.rip = reg.rip + sizeof(inst_t);
}
void move_reg_mem_handler(uint64_t src, uint64_t dst)
{
    //src: reg
    //dst: virtual address
    write64bits_dram(va2pa(dst), *(uint64_t *)src);
    reg.rip = reg.rip + sizeof(inst_t);
}
void call_handler(uint64_t src, uint64_t dst)
{
    reg.rsp = reg.rsp - 8;
    //write return address to rsp memory
    write64bits_dram(va2pa(reg.rsp), reg.rip + sizeof(inst_t));
    reg.rip = src;    
}

void push_reg_handler(uint64_t src, uint64_t dst)
{
    reg.rsp = reg.rsp - 0x8;
    write64bits_dram(va2pa(reg.rsp  ), *(uint64_t *)src);
    reg.rip = reg.rip + sizeof(inst_t);    
}
void pop_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t*)src = read64bits_dram(va2pa(reg.rsp));
    reg.rsp += 8;
    reg.rip = reg.rip + sizeof(inst_t);    
}

void retq_handler(uint64_t src, uint64_t dst)
{
    reg.rip = read64bits_dram(va2pa(reg.rsp)); 
    reg.rsp += 8;    
}

void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}