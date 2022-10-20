CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = multimsg

all: $(PROGRAMS)

multimsg: multimsg.c
	$(CC) $(CFLAGS) -o multimsg multimsg.c

clean:
	rm -f multimsg