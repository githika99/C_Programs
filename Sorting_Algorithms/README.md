<h1>Description</h1>
The sorting algorithms of this project have errors. For this project, shell sort, heap sort, quick sort, and batcher sort are ran using sorting.c. To modify the execution of the various sorts, follow the instructions below.

<h2>Builidng</h2>
$ make

<h2>Running</h2>
$ ./sorting

<h3>Options</h3>
SYNOPSIS
<br>	A collection of comparison-based sorting algorithms.
<br><br>
	USAGE
<br>	./sorting\_arm64 [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]
<br><br>
OPTIONS<br>
   -H              Display program help and usage.<br>
   -a              Enable all sorts.<br>
   -s              Enable Shell Sort.<br>
   -b              Enable Batcher Sort.<br>
   -h              Enable Heap Sort.<br>
   -q              Enable Quick Sort.<br>
   -n length       Specify number of array elements (default: 100).<br>
   -p elements     Specify number of elements to print (default: 100).<br>
   -r seed         Specify random seed (default: 13371453).<br>
<br>
<h3>Cleaning</h3>
$ make clean



<h1>Bugs</h1>
For 
$ ./sorting -a

batcher sort does not print the number of moves.

But for 
$ ./sorting -b

it does print the number of moves.

I made set.c but did not use it in sorting.c. I did not use sets at all in the testing harness.
