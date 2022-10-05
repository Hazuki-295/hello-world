CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = show-bytes

all: $(PROGRAMS)

show-bytes: show-bytes.c
	$(CC) $(CFLAGS) -o show-bytes show-bytes.c

run:
	./show-bytes 12345

clean:
	rm -f show-bytes