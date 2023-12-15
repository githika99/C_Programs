#include <stdio.h>
#include <stdint.h>
#include "stats.h"
#include "shell.h"
#include "gaps.h"

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length)
{
	uint32_t j;
	uint32_t temp;
	int n = 0;
	uint32_t gap = gaps[n];

	while(gap > 0)
	{
		for(uint32_t i = gap; i < length; i++)
		{
			j = i;
			temp = arr[i];
			//compare = cmp(stats, arr[j - gap], temp);
			while((j >= gap) && (cmp(stats, arr[j - gap], temp) == 1))	//use cmp() to do temp < arr[j - gap]
				{
				arr[j] = arr[j - gap];			//use move function
				move(stats, arr[j]);
				j -= gap;
				}
			arr[j] = temp;
			move(stats, arr[j]);
		}
		n++;
		gap = gaps[n];
	}
}

/*
int main (void)
{

	uint32_t arr[] = {8,7,6,5,4, 3, 2, 1, 10,9};
	uint32_t length = 10;
	Stats stats;
	stats.moves = 0;
	stats.compares = 0;

	shell_sort(&stats, arr, length);
	for (int i = 0; i < length; i++)
		printf("%d\t", arr[i]);
return 0;
}
*/
