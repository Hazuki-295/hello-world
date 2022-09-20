CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = sum

all: $(PROGRAMS)

sum: main.c sum.c
	$(CC) $(CFLAGS) -o prog main.c sum.c -v

clean:
	rm -f prog