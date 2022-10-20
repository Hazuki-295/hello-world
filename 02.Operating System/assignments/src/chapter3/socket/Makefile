JC = javac
JFLAGS = -g

PROGRAMS = socket

CLASSES = \
        DateClient.java \
        DateServer.java

all: $(PROGRAMS)

socket:
	$(JC) $(JFLAGS) $(CLASSES)

clean:
	rm -f *.class