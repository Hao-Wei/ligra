CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g

all: test

test: test.cpp boruvka.h
	$(CC) $(CFLAGS) -o test test.cpp boruvka.h

clean:
	rm -f *.o test
