CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = hello

all: $(PROGRAMS)

echo: hello.c
	$(CC) $(CFLAGS) -o hello hello.c -pthread

clean:
	rm -f hello