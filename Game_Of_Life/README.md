The Game of Life should be played on a potentially infinite, two-dimensional (2-D) grid of cells that
represents a universe. Each cell has two possible states: it is either dead or alive. The game progresses
through generations, what some might call “steps in time.” There are only three rules that determine the
state of the universe after each generation:
1. Any live cell with two or three live neighbors survives.
2. Any dead cell with exactly three live neighbors becomes a live cell.
3. All other cells die, either due to loneliness or overcrowding.

The animation does not work, but the rest project does. 

(ncurses does not print out anything, it is always set to false). 

For this project, life.c contains a main function and universe.c contains many other functions used by the main function.

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
