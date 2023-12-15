SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: sorting

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c batcher.c

sorting: sorting.o stats.o batcher.o shell.o quick.o heap.o 
	$(CC) -o sorting sorting.o stats.o batcher.o shell.o quick.o heap.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.[ch]

