CC = gcc
CFLAGS = -arch x86_64

all:	assign2

exponent.o:	exponent.s
	$(CC) $(CFLAGS) -c exponent.s

assign2:	main.o functions.o exponent.o
	$(CC) $(CFLAGS) -o assign2 main.o functions.o exponent.o

