CC=gcc
CFLAGS=-Wall
LDFLAGS=-lm

# Target to compile the entire program
all: ass1

# Link the object file and create the executable
ass1: randgen1.o
	$(CC) randgen1.o -o ass1 $(LDFLAGS)

# Compile the source file into an object file
randgen1.o: randgen1.c
	$(CC) $(CFLAGS) -c randgen1.c

# Clean the build directory
clean:
	rm -f *.o ass1
