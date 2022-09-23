CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = prog

all: $(PROGRAMS)

prog: main.c addvec.c multvec.c
# Create a static library of these two vector operations
	$(CC) $(CFLAGS) -c addvec.c multvec.c
	ar rcs libvector.a addvec.o multvec.o
# Build the executable that contains main.o which invokes the addvec library routine
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -static -o prog main.o libvector.a

clean:
	rm -r prog *.o *.a