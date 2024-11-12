CC = gcc
CFLAGS = -arch x86_64

all:	assign3

assignment3.o:	assignment3.s
	$(CC) $(CFLAGS) -c assignment3.s

assign3:	heap.o assignment3.o
	$(CC) $(CFLAGS) -o assign3 heap.o assignment3.o

