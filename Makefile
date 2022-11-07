
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

validate-binary-search-tree: validate-binary-search-tree.o
	$(CC) $(CFLAGS) -o validate-binary-search-tree validate-binary-search-tree.o

validate-binary-search-tree.o: validate-binary-search-tree.cpp
	$(CC) $(CFLAGS) -c validate-binary-search-tree.cpp

clean:
	rm -rf validate-binary-search-tree validate-binary-search-tree.o
