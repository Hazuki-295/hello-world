CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = relocatable

all: $(PROGRAMS)

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