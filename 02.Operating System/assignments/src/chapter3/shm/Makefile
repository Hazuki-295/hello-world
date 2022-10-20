CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = shm

all: $(PROGRAMS)

shm: shm-posix-producer.c shm-posix-consumer.c
	$(CC) $(CFLAGS) -o shm-posix-producer shm-posix-producer.c -lrt
	$(CC) $(CFLAGS) -o shm-posix-consumer shm-posix-consumer.c -lrt

run:
	./shm-posix-producer
	./shm-posix-consumer

clean:
	rm -f shm-posix-producer shm-posix-consumer