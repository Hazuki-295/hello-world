CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = shell

all: $(PROGRAMS)

shell: shell.c
	$(CC) $(CFLAGS) -o shell shell.c

clean:
	rm -f shell