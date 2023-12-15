//#pragma once

#include "stats.h"
#include "quick.h"
#include <stdio.h>
#include <stdint.h>

void quick_sort(Stats *stats, uint32_t *A, uint32_t n);

//make quick_sort the appropriate format, use swap() and cmp() from stats.c

uint32_t partition (Stats *stats, uint32_t A[], uint32_t lo, uint32_t hi)
{
	uint32_t i = lo - 1;
	int compare;
	for (uint32_t j = lo; j < hi; j++)
	{
		compare = cmp(stats, A[j - 1], A[hi - 1]);
		if (compare == -1)		//uses cmp() to do A[j - 1] < A[hi - 1]
		{
			i++;
			//swap A[j - 1] and  A[i - 1] 
			swap(stats, &A[j - 1],  &A[i - 1]);
		}
	}	
	//swap A[i] and A[hi - 1]
	swap(stats, &A[i],  &A[hi - 1]);
	return (i + 1);
}

void quick_sorter(Stats *stats, uint32_t A[], uint32_t lo, uint32_t hi)
{
	uint32_t p;
	if (lo < hi)
	{
		p = partition(stats, A, lo, hi);
		quick_sorter(stats, A, lo, p - 1);
		quick_sorter(stats, A, p + 1, hi);
	}
}


void quick_sort(Stats *stats, uint32_t *A, uint32_t n)
{
	quick_sorter(stats, A, 1, n);
}

/*
int main ()
{
	Stats quick_stat;
	quick_stat.moves = 0;
	quick_stat.compares = 0;
	uint32_t A[] = {5,3,8,2,9,10,1,7,4,6};
	uint32_t length = 10;
	quick_sort(&quick_stat, A, length);
	for (int i = 0; i < length; i++)
		printf("%d\t", A[i]);
	
	return 0;
}
*/
