CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = relocatable

all: $(PROGRAMS)

relocatable: main.c
# run the compiler and assembler, generate relocatable object file - main.o
	$(CC) $(CFLAGS) -c main.c
# print the size of main.o (in bytes)
	wc -c main.o
# display the ELF header of the relocatable object file main.o
	readelf -h main.o > ELF_header.txt

clean:
	rm -rf *.o *.txt