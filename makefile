CC = /usr/bin/gcc-7
CFLAGS = -Wall -g -O2 -Werror -std=gnu99

SRC = ./src

EXE = csapp

CODE = ./src/memory/instruction.c ./src/disk/code.c ./src/memory/dram.c ./src/cpu/mmu.c ./src/main.c

.PHONY: csapp
csapp: 
	$(CC) $(CFLAGS)	-I $(SRC) $(CODE) -o $(EXE)
run:
	./$(EXE)