CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = prog

all: $(PROGRAMS)

prog: addvec.c multvec.c main.c
# Create a static library libvector.a of these two vector routines
	$(CC) $(CFLAGS) -c addvec.c multvec.c
	ar rcs libvector.a addvec.o multvec.o
# Build the executable object file prog whith contains main.o that invokes the addvec library routine
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -static -o prog main.o ./libvector.a
# run prog
	./prog

clean:
	rm -r prog *.o *.a