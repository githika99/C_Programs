#include "stats.h"
#include "shell.h"
#include "quick.h"
#include "heap.h"
#include "batcher.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#define OPTIONS "ahbsqr:n:p:H"

//header functions to print the appropriate responses
void shellsort(uint32_t A[], uint32_t length, uint32_t elements){
	Stats shell_stat;
	shell_stat.moves = 0;
	shell_stat.compares = 0;
	shell_sort(&shell_stat, A, length);
	printf("\nShell Sort, %u elements, %lu moves, %lu compares\n", length, shell_stat.moves, shell_stat.compares);
	for (uint32_t i = 0; i < elements; i++)
	{
	printf("%-15d\t", A[i] );
	if ((i+1) % 5 == 0)
		printf("\n");
	}
}


void quicksort(uint32_t A[], uint32_t length, uint32_t elements){
        Stats quick_stat;
        quick_stat.moves = 0;
        quick_stat.compares = 0;
        quick_sort(&quick_stat, A, length);
        printf("\nQuick Sort, %u elements, %lu moves, %lu compares\n", length, quick_stat.moves, quick_stat.compares);
	for (uint32_t i = 0; i < elements; i++)
        {
        printf("%-15d\t", A[i] );
        if ((i+1) % 5 == 0)
                printf("\n");
        }

}

void batchersort(uint32_t A[], uint32_t length, uint32_t elements){
        Stats batcher_stat;
        batcher_stat.moves = 0;
        batcher_stat.compares = 0;
        batcher_sort(&batcher_stat, A, length);
        printf("\nBatcher Sort, %u elements, %lu moves, %lu compares\n", length, batcher_stat.moves, batcher_stat.compares);
	for (uint32_t i = 0; i < elements; i++)
        {
        printf("%-15d\t", A[i] );
        if ((i+1) % 5 == 0)
                printf("\n");
        }
}

void heapsort(uint32_t A[], uint32_t length,uint32_t elements){
        Stats heap_stat;
        heap_stat.moves = 0;
        heap_stat.compares = 0;
        heap_sort(&heap_stat, A, length);
        printf("\nHeap Sort, %u elements, %lu moves, %lu compares\n", length, heap_stat.moves, heap_stat.compares);
        for (uint32_t i = 0; i < elements; i++)
        {
        printf("%-15d\t", A[i] );
        if ((i+1) % 5 == 0)
                printf("\n");
        }

}



int main(int argc, char **argv) {
   int opt = 0;

   uint32_t seed = 13371453;
  uint32_t size = 100;
  uint32_t elements = 100;
	int a = 0;
	int h = 0;
	int b = 0;
	int s = 0;
	int q = 0;


   while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

      switch(opt) {
	case 'a': a = 1;
               break;

	case 'h': h = 1;
               break;
	
	case 'b': b = 1;
               break;

	case 's': s = 1;
               break;

	case 'q': q = 1;
               break;

	case 'r': seed = (uint32_t)strtoul(optarg, NULL, 10);;
               break;

	case 'n': size = (uint32_t)strtoul(optarg, NULL, 10); elements = size;
               break;

	case 'p': elements  = (uint32_t)strtoul(optarg, NULL, 10);
               break;

	case 'H': printf("SYNOPSIS\n\tA collection of comparison-based sorting algorithms.\n\n\tUSAGE\n\t./sorting_arm64 [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n   -H              Display program help and usage.\n   -a              Enable all sorts.\n   -s              Enable Shell Sort.\n   -b              Enable Batcher Sort.\n   -h              Enable Heap Sort.\n   -q              Enable Quick Sort.\n   -n length       Specify number of array elements (default: 100).\n   -p elements     Specify number of elements to print (default: 100).\n   -r seed         Specify random seed (default: 13371453).");
		  break;
      }
   }

   	
   	srandom(seed);
   	uint32_t A[size];
	for (uint32_t i = 0; i < size; i++)
		A[i] = random();

	if (a == 1)
	{
		shellsort(A, size, elements);
		quicksort(A, size, elements);
		heapsort(A, size, elements);
		batchersort(A, size, elements);
	}

	if(b ==1)
		batchersort(A, size, elements);

	if(s == 1)
		shellsort(A, size, elements);

	if(q == 1)
		quicksort(A, size, elements);

	if(h == 1)
		heapsort(A, size, elements);
return 0;
}
