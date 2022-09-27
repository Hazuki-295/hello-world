CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = sigint

all: $(PROGRAMS)

sigint: sigint.c
	$(CC) $(CFLAGS) -o sigint sigint.c

clean:
	rm -f sigint