CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = kill

all: $(PROGRAMS)

kill: kill.c
	$(CC) $(CFLAGS) -o kill kill.c

clean:
	rm -f kill