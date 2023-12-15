ncurses does not print out anything, it is always set to false.

For this assignment, life.c contains a main function and universe.c contains many other functions used by the main function.

Building
$ make

Running
$ ./life -[Options]

Options
i: file with the input (stdin by default)
o: file that output should be written to (stdout by default)
n: generations that you want the game to run (default is 0)
s: silences ncurses. (in my program, ncurses is always false and you cannot set it to true)

Cleaning:
$ make clean
