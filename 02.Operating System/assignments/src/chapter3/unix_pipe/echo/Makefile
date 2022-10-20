CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = echo

all: $(PROGRAMS)

echo: echo.c
	$(CC) $(CFLAGS) -o echo echo.c

clean:
	rm -f echo