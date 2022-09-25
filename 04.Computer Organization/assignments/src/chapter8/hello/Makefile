CC = gcc
CFLAGS = -Og -m64 -Wall

PROGRAMS = hello

hello: hello.c
# hello program written using the write system-level function instead of printf
	$(CC) $(CFLAGS) -o hello hello.c
# disassemble the hello executeable
	objdump -d hello > hello.64d
# run hello
	./hello

hello-asm64: hello-asm64.s
# hello-asm64.s is a handwritten asm program for syscalls using the x86-64 convention
	$(CC) -m64 -static -o hello-asm64 hello-asm64.s
# run hello-asm64
	./hello-asm64

clean:
	rm -f hello hello-asm64 *.64d