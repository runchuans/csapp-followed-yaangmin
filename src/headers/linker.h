#ifndef LINKER_GUARD
#define LINKER_GUARD

#include<stdint.h>
#include<stdlib.h>


#define MAX_CHAR_SECTION_NAME (32)
typedef struct
{
    char sh_name[MAX_CHAR_SECTION_NAME];
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;/* data */
} sht_entry_t;


typedef enum 
{
    GLOBAL,
    LOCAL,
    WEAK
} st_bind_t;

typedef enum
{
    NOTYPE,
    OBJECT,
    FUNC
} st_type_t;


#define MAX_CHAR_SYMBOL_NAME (64)
typedef struct 
{
    char st_name[MAX_CHAR_SYMBOL_NAME];
    st_bind_t bind;
    st_type_t type;
    char st_shndex[MAX_CHAR_SECTION_NAME];
    uint64_t st_value; //in_section offset
    uint64_t st_size;   //count of line of symbal
} st_entry_t;

#define MAX_ELF_FILE_LENGTH (64) //max 64 effective line
#define MAX_ELF_FILE_WIDTH (128) // max 128 chars per line

typedef struct 
{
    char buffer[MAX_ELF_FILE_LENGTH][MAX_ELF_FILE_WIDTH];
    uint64_t linescount;
    sht_entry_t *sht;
} elf_t;

#endif