CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = integer-arithmetic

all: $(PROGRAMS)

integer-arithmetic: uaddcheck.c
	$(CC) $(CFLAGS) -o uaddcheck uaddcheck.c

clean:
	rm -f uaddcheck