//#pragma once
#include <stdint.h>
#include "stats.h"
#include "heap.h"
#include <stdio.h>
#include <inttypes.h>

void heap_sort(Stats *stats, uint32_t *A, uint32_t n);


//add swap() funct and cmp() funct from stats.c

//we use 1 based index for tree and 0 based index for array
//returns index of max child
uint32_t max_child(Stats *stats, uint32_t A[], uint32_t first, uint32_t last)
{
	uint32_t left = 2 * first;
	uint32_t right = left + 1;
	int compare;
	compare = cmp(stats, A[right - 1],  A[left - 1]);
	if (right <= last && (compare == 1))	//use cmp() to do A[right - 1] > A[left - 1]
		return right;
	return left;
}


void fix_heap(Stats *stats, uint32_t A[], uint32_t first, uint32_t last)
{
	int found = 0;		//boolean for found variable (0 - false) (1 - true)
	int compare;
	uint32_t mother = first;
	uint32_t great = max_child(stats, A, mother, last);

	while (mother <= (last / 2) && !(found))
	{ 
		compare = cmp(stats, A[mother - 1],  A[great - 1] );
		if (compare == -1)		//use cmp() to do A[mother - 1] < A[great - 1]
			{
			//swap A[mother -1] and A[great - 1]
			swap( stats, &A[mother -1], &A[great -1] );
			mother = great;
			great = max_child(stats, A, mother, last);
			}		
		else
			found = 1;
	}
}

void build_heap(Stats *stats, uint32_t A[], uint32_t first, uint32_t last)
{
	for (uint32_t father = (last/2); father > (first - 1); father--)
		fix_heap(stats, A, father, last);
}


void heap_sort(Stats *stats, uint32_t *A, uint32_t n)	//match to funct declaration.
{
	int first = 1;
	int last = n;
	build_heap(stats, A, first, last);
	for (int leaf = last; leaf > first; leaf--)
	{
		//swap A[first - 1] and A[leaf - 1]
		swap( stats, &A[first -1], &A[leaf-1] );
		fix_heap(stats, A, first, leaf - 1);
	}
}


