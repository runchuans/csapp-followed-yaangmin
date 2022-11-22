#include <stdio.h>
#include <stdlib.h>
#include "cpu/register.h"
#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "memory/dram.h"

int main() 
{
    init_handler_table();

    //init
    reg.rax = 0x12340000;
    reg.rbx = 0x0;
    reg.rcx = 0x555555554660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7fffffffdf08;
    reg.rdi = 0x1;
    reg.rbp = 0x7fffffffde20;
    reg.rsp = 0x7fffffffde00;

    reg.rip = (uint64_t)&program[11];

       
    write64bits_dram(va2pa(0x7fffffffde20), 0x555555554660); //rbp
    write64bits_dram(va2pa(0x7fffffffde18), 0x0);
    write64bits_dram(va2pa(0x7fffffffde10), 0xabcd);
    write64bits_dram(va2pa(0x7fffffffde08), 0x12340000);
    write64bits_dram(va2pa(0x7fffffffde00), 0x555555554660); //rsp

    // print_register();
    // print_stack();
    // uint64_t pa = va2pa(0x7fffffffde20);
    // printf("16jinzhi%lx\n",read64bits_dram(pa));
    //run list
    for(int i = 0; i < 15; i ++)
    {
        instruction_cycle();
        print_register();
        print_stack();
    }
     
    //verify
    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x555555554660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7fffffffde20);
    match = match && (reg.rsp == 0x7fffffffde00);
    if (match == 1)
    {
        printf("register match\n");
    }
    else
    {
        printf("register not match\n");
    }

    match = match && (read64bits_dram(va2pa(0x7fffffffde20)) == 0x0000555555554660); //rbp
    match = match && (read64bits_dram(va2pa(0x7fffffffde18)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7fffffffde10)) == 0xabcd);
    match = match && (read64bits_dram(va2pa(0x7fffffffde08)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7fffffffde00)) == 0x0000555555554660); //rsp
    if (match == 1)
    {
        printf("memory match\n");
    }
    else
    {
        printf("memory not match\n");
    }    
    return 0;
}