CC = gcc
CFLAGS = -Og -m64 -Wall

.PHONY: foobar1 foobar2 foobar3 foobar4 foobar5 foobar6

###################################################
# These following are supposed to fail at link time
linkerror: linkerror.c
# Expected to fail
	$(CC) $(CFLAGS) -o linkerror linkerror.c

foobar1: foobar1/foo1.c foobar1/bar1.c
# Expected to fail
	cd foobar1 && \
	$(CC) $(CFLAGS) -o foobar1 foo1.c bar1.c

foobar2: foobar2/foo2.c foobar2/bar2.c
# Expected to fail
	cd foobar2 && \
	$(CC) $(CFLAGS) -o foobar2 foo2.c bar2.c
###################################################

foobar3: foobar3/foo3.c foobar3/bar3.c
	cd foobar3 && \
	$(CC) $(CFLAGS) -o foobar3 foo3.c bar3.c && \
	./foobar3

foobar4: foobar4/foo4.c foobar4/bar4.c
	cd foobar4 && \
	$(CC) $(CFLAGS) -o foobar4 foo4.c bar4.c && \
	./foobar4

# This one is supposed to generate a compiler warning
foobar5: foobar5/foo5.c foobar5/bar5.c
	cd foobar5 && \
	$(CC) $(CFLAGS) -o foobar5 foo5.c bar5.c && \
	./foobar5

clean:
	rm -f foobar*/foobar*