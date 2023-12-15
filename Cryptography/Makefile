SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -gdwarf-4 $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --cflags gmp)

OBJS = keygen.o decrypt.o encrypt.o numtheory.o randstate.o ss.o
OBJ_KEYGEN = keygen.o numtheory.o randstate.o ss.o
OBJ_ENCRYPT = encrypt.o numtheory.o randstate.o ss.o
OBJ_DECRYPT = decrypt.o numtheory.o randstate.o ss.o

all: keygen encrypt decrypt

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c -lgmp

numtheory.o: numtheory.c numtheory.h randstate.c
	$(CC) $(CFLAGS) -c numtheory.c randstate.c -lgmp

ss.o: ss.c ss.h numtheory.c randstate.c
	$(CC) $(CFLAGS) -c ss.c numtheory.c randstate.c -lgmp -lm

keygen: keygen.o numtheory.o randstate.o ss.o
	$(CC) -o keygen keygen.o numtheory.o randstate.o ss.o $(LIBS)

encrypt: encrypt.o numtheory.o randstate.o ss.o
	$(CC) -o encrypt encrypt.o numtheory.o randstate.o ss.o $(LIBS)

decrypt: decrypt.o numtheory.o randstate.o ss.o
	$(CC) -o decrypt decrypt.o numtheory.o randstate.o ss.o $(LIBS)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c numtheory.c randstate.c ss.c -lgmp

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c numtheory.c randstate.c ss.c -lgmp -lm

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c numtheory.c randstate.c ss.c -lgmp -lm

clean:
	rm -f *.o keygen encrypt decrypt

format:
	clang-format -i -style=file *.[ch]
