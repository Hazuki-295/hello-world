CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = relocatable

all: $(PROGRAMS)

relocatable: main.c
# run the compiler and assembler, generate relocatable object file - main.o
	gcc -c main.c
# print the size of main.o (in bytes)
	wc -c main.o
# display all non-empty sections
	objdump -s -d -x --wide main.o > 00.Disassemble.txt
# display information about the ELF file main.o
	readelf -a main.o --wide > 00.Readelf_all.txt
# 01.display the ELF header
	readelf -h main.o > 01.ELF_header.txt
# 02.display the Section header table
	readelf -S main.o --wide > 02.Section_headers.txt
# 03.display the symbol table (.symtab section)
	readelf -s main.o > 03.Symbol_table.txt
clean:
	rm -rf *.o *.txt