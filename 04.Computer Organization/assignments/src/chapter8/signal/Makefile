CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = signal

all: $(PROGRAMS)

signal: signal.c
	$(CC) $(CFLAGS) -o signal signal.c

clean:
	rm -f signal