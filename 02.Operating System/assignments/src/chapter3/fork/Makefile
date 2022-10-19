CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = fork

all: $(PROGRAMS)

fork: fork.c
	$(CC) $(CFLAGS) -o fork fork.c

clean:
	rm -f fork