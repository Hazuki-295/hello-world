CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = unix_pipe

all: $(PROGRAMS)

unix_pipe: unix_pipe.c
	$(CC) $(CFLAGS) -o unix_pipe unix_pipe.c

clean:
	rm -f unix_pipe