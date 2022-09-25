CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = branch

all: $(PROGRAMS)

branch: branch.c
# run the compiler, generate assembly code - mstore.s
	$(CC) $(CFLAGS) -c branch.c
	$(CC) $(CFLAGS) -o branch branch.c
# run the disassembler to generate disassembly code before and after running the linker
	objdump -d branch.o > branch.64d
	objdump -d branch > branch_linked.64d

highlight: branch
	mv branch.64d branch.asm
	mv branch_linked.64d branch_linked.asm

clean:
	rm -f branch *.o *.64d *.asm