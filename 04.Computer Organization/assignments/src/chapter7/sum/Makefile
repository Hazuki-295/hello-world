CC = gcc
CFLAGS = -Og -m64 -Wall
SYSTEM-OBJECT-FILES = /usr/lib/x86_64-linux-gnu/crt1.o \
/usr/lib/x86_64-linux-gnu/crti.o \
/usr/lib/gcc/x86_64-linux-gnu/9/crtbeginT.o \
-L/usr/lib/gcc/x86_64-linux-gnu/9 \
-L/usr/lib \
--start-group -lgcc -lgcc_eh -lc --end-group \
/usr/lib/gcc/x86_64-linux-gnu/9/crtend.o \
/usr/lib/x86_64-linux-gnu/crtn.o

PROGRAMS = sum

all: $(PROGRAMS)

sum: main.c sum.c
# run the C preprocessor (cpp), expand the source code - main.i, sum.i
	mkdir -p tmp

	cpp main.c ./tmp/main.i
	cpp sum.c ./tmp/sum.i

# run the C compiler (cc1), generate assembly-language file - main.s, sum.s
	cc1 ./tmp/main.i -Og -o ./tmp/main.s
	cc1 ./tmp/sum.i -Og -o ./tmp/sum.s

# run the assembler (as), generate binary relocatable object file - main.o, sum.o
	as ./tmp/main.s -o ./tmp/main.o
	as ./tmp/sum.s -o ./tmp/sum.o

# run the linker program (ld), generate binary executable object file - prog
	ld -static -o prog ./tmp/main.o ./tmp/sum.o $(SYSTEM-OBJECT-FILES)

clean:
	rm -rf prog tmp