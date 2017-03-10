CC=gcc
CFLAGS=-std=c11 -I.
DEPS=alphabet.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

alphabet: alphabet.o 
	gcc -o alphabet alphabet.o -std=c11 -I.
