CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = relocatable

all: $(PROGRAMS)

relocatable: main.c
# run the compiler and assembler, generate relocatable object file - main.o
	$(CC) $(CFLAGS) -c main.c
# print the size of main.o (in bytes)
	wc -c main.o
# display display all information about the relocatable object file main.o
	readelf -a main.o --wide > Readelf_all.txt
# display the ELF header of the file main.o
	readelf -h main.o > ELF_header.txt
# display the Section header table of the file main.o
	readelf -S main.o --wide > Section_headers.txt

clean:
	rm -rf *.o *.txt