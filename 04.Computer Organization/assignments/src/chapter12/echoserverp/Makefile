CC = gcc
CFLAGS = -Og -m64 -Wall
CSAPP =  ../../src/csapp.c

PROGRAMS = echo

all: $(PROGRAMS)

echo: echoserverp.c echoclient.c
	$(CC) $(CFLAGS) -o echoclient echoclient.c $(CSAPP) -pthread
	$(CC) $(CFLAGS) -o echoserverp echoserverp.c $(CSAPP) -pthread

run-server: echo
	./echoserverp 8080

run-client: echo
	./echoclient localhost 8080

clean:
	rm -f echoclient echoserverp