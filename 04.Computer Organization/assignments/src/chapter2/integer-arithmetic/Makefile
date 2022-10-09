CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = integer-arithmetic

all: $(PROGRAMS)

integer-arithmetic: uaddcheck.c taddcheck.c tsubcheck.c
	$(CC) $(CFLAGS) -o uaddcheck uaddcheck.c
	$(CC) $(CFLAGS) -o taddcheck taddcheck.c
	$(CC) $(CFLAGS) -o tsubcheck tsubcheck.c

clean:
	rm -f uaddcheck taddcheck tsubcheck