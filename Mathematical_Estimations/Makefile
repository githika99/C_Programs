SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: mathlib-test

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

euler.o: euler.c
	$(CC) $(CFLANGS) -c euler.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

mathlib-test: e.o euler.o viete.o newton.o madhava.o bbp.o mathlib-test.o
	$(CC) -o mathlib-test e.o euler.o viete.o newton.o madhava.o bbp.o mathlib-test.o -lm

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c 

clean:
	rm -f mathlib-test *.o mathlib-test

format:
	clang-format -i -style=file *.[ch]
