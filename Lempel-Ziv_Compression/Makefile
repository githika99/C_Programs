SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -gdwarf-4 $(shell pkg-config --cflags gmp)
LIBS = $(shell pkg-config --libs gmp)

all:encode decode

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

word.o: word.c word.h
	$(CC) $(CFLAGS) -c word.c

encode: io.o trie.o encode.o
	$(CC) -o encode io.o trie.o encode.o $(LIBS)

decode: io.o word.o decode.o
	$(CC) -o decode io.o word.o decode.o $(LIBS)

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c io.c trie.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c io.c word.c

clean:
	rm -f *.o encode decode

format:
	clang-format -i -style=file *.[ch]

