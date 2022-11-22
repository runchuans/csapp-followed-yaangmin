#ifndef instruction_guard
#define instruction_guard
#include<stdlib.h>
#include<stdint.h>



#define NUM_INSTRUCTION 30


typedef enum OP   // operator
{
    push_reg,
    mov_reg_reg, 
    mov_reg_mem,
    mov_mem_reg,
    pop_reg,
    retq,
    call, 
    add_reg_reg
} op_t;

typedef enum ODTYPE //operand type
{
    EMPTY,IMM, REG,
    MM_IMM, MM_REG, MM_IMM_REG, MM_REG1_REG2,
    MM_IMM_REG1_REG2, MM_REG2_S, MM_IMM_REG2_S,
    MM_REG1_REG2_S, MM_IMM_REG1_REG2_S
} od_type_t;

typedef struct OD // operand
{
    od_type_t type;
    int64_t imm; //imm can be negative number
    int64_t scal;
    uint64_t *reg1;
    uint64_t *reg2;
    
} od_t;


typedef struct INSRUCT_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
    char code[100];
}inst_t;

#define INST_LEN 100
inst_t program[INST_LEN];
uint64_t decode_od(od_t od);
void instruction_cycle();


//pointer pointing to the function
typedef void(*handler_t)(uint64_t, uint64_t);

void init_handler_table();
handler_t handler_table[NUM_INSTRUCTION];
void call_handler(uint64_t src, uint64_t dst);
void move_reg_mem_handler(uint64_t src, uint64_t dst);
void push_reg_handler(uint64_t src, uint64_t dst);
void add_reg_reg_handler(uint64_t src, uint64_t dst);
void move_reg_reg_handler(uint64_t src, uint64_t dst);
void move_mem_reg_handler(uint64_t src, uint64_t dst);
void pop_reg_handler(uint64_t src, uint64_t dst);
void retq_handler(uint64_t src, uint64_t dst);
#endif