CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = prog

all: $(PROGRAMS)

prog: main.c sum.c
# build executable
	$(CC) $(CFLAGS) -o prog main.c sum.c
# print section sizes of prog
	size prog
# print the Section header table
	readelf prog -S --wide > 01.Section_headers.txt
# locate the number of .bss section
	grep .bss 01.Section_headers.txt
# print the symbol table
	readelf prog -s > 02.Symbol_table.txt
# locate the symbols within the .bss section
	grep 26 02.Symbol_table.txt

relocatable: main.c
# backup the Makefile
	mv Makefile Makefile.bak
# a confusing operation
	cp ../relocatable/Makefile ./ && make
# restore the Makefile
	rm Makefile && mv Makefile.bak Makefile

executable: main.c sum.c
# backup the Makefile
	mv Makefile Makefile.bak
# a confusing operation
	cp ../executable/Makefile ./ && make
# restore the Makefile
	rm Makefile && mv Makefile.bak Makefile
# run prog
	./prog

clean:
	rm -rf prog *.o *.txt