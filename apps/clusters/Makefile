CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g

all: test

test: test.cpp boruvka.h boruvka2.h boruvka3.h kruskal.h kruskal2.h common.h
	$(CC) $(CFLAGS) -o test test.cpp boruvka.h boruvka2.h boruvka3.h kruskal.h kruskal2.h common.h

clean:
	rm -f *.o test
