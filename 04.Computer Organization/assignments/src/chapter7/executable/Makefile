CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = executable

all: $(PROGRAMS)

executable: main.c sum.c
# run the compiler driver, generate executable object file - prog
	$(CC) $(CFLAGS) -o prog main.c sum.c
# display all non-empty sections
	objdump -s -d -x --wide prog > 00.Disassemble.txt
# display information about the ELF file prog
	readelf -a prog --wide > 00.Readelf_all.txt
# 01.display the ELF header
	readelf -h prog > 01.ELF_header.txt
# 02.display the Program header table
	readelf -l prog --wide > 02.Program_headers.txt
# 03.display the Section header table
	readelf -S prog --wide > 03.Section_headers.txt
# 04.display the symbol table (.symtab section)
	readelf -s prog > 04.Symbol_table.txt

clean:
	rm -rf prog *.o *.txt