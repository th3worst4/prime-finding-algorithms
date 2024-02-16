CC = gcc
CFLAGS = -m64 -g -lm

primes: main.o
	$(CC) $(CFLAGS) main.o -o primes

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
