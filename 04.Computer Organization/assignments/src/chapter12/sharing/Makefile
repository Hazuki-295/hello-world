CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = sharing

all: $(PROGRAMS)

sharing: sharing.c
	$(CC) $(CFLAGS) -o sharing sharing.c -pthread

clean:
	rm -f sharing