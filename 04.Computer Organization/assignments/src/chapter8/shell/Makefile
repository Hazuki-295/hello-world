CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = shell

all: $(PROGRAMS)

shell: shell.c
	$(CC) $(CFLAGS) -o shell shell.c

run: shell
	cd ../myecho && make
	echo "../myecho/myecho everyting is OK" | ./shell
	cd ../myecho && make clean

clean:
	rm -f shell