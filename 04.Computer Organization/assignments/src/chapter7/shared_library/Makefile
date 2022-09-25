CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = prog

all: $(PROGRAMS)

prog: addvec.c multvec.c main.c
# Create a shared library libvector.so of these two vector routines
	gcc -shared -fpic -o libvector.so addvec.c multvec.c
# Build the executable object file prog in a form that can be linked with libvector.so at run time
	gcc -o prog main.c ./libvector.so
# run prog
	./prog

clean:
	rm -r prog *.so