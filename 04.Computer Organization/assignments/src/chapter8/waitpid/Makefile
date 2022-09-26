CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = waitpid

all: $(PROGRAMS)

waitpid: waitpid1.c waitpid2.c
	$(CC) $(CFLAGS) -o waitpid1 waitpid1.c
	$(CC) $(CFLAGS) -o waitpid2 waitpid2.c

clean:
	rm -f waitpid1 waitpid2