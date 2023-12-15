SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: life

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

life: life.o universe.o
	$(CC) -o life life.o universe.o -lncurses

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

clean:
	rm -f *.o life

format:
	clang-format -i -style=file *.[ch]


