CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = myecho

all: $(PROGRAMS)

myecho: myecho.c
	$(CC) $(CFLAGS) -o myecho myecho.c

run: myecho
	./myecho everyting is OK

clean:
	rm -f myecho