CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = main

all: $(PROGRAMS)

main: main.c
# backup the Makefile
	mv Makefile Makefile.bak
# a confusing operation
	cp ../relocatable/Makefile ./ && make
# restore the Makefile
	rm Makefile && mv Makefile.bak Makefile

clean:
	rm -rf *.o *.txt