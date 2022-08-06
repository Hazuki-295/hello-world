CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = mstore

all: $(PROGRAMS)

mstore: mstore.c main.c
# run the compiler, generate assembly code - mstore.s
	$(CC) $(CFLAGS) -S mstore.c

# run the compiler and assembler, generate object-code - mstore.o
	$(CC) $(CFLAGS) -c mstore.c

# run the compiler, assembler and linker to generate executable code - prog
	$(CC) $(CFLAGS) -o prog main.c mstore.c

# run the disassembler to generate disassembly code before and after running the linker
	objdump -d mstore.o > mstore.64d
	objdump -d prog > prog.64d

highlight: mstore
	mv mstore.s mstore.asm
	mv mstore.64d mstore_d.asm
	mv prog.64d prog_d.asm

clean:
	rm -f prog *.s *.o *.64d *.asm