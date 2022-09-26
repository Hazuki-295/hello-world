CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = myecho

all: $(PROGRAMS)

myecho: myecho.c
	$(CC) $(CFLAGS) -o myecho myecho.c

clean:
	rm -f myecho