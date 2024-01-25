#include <stdio.h>
#include <stdint.h>

typedef struct {
   uint64_t moves;
   uint64_t compares;
} Stats;

static uint32_t const gaps[] = {1024
                               , 972
                               , 864
                               , 768
                               , 729
                               , 648
                               , 576
                               , 512
                               , 486
                               , 432
                               , 384
                               , 324
                               , 288
                               , 256
                               , 243
                               , 216
                               , 192
                               , 162
                               , 144
                               , 128
                               , 108
                               , 96
                               , 81
                               , 72
                               , 64
                               , 54
                               , 48
                               , 36
                               , 32
                               , 27
                               , 24
                               , 18
                               , 16
                               , 12
                               , 9
                               , 8
                               , 6
                               , 4
                               , 3
                               , 2
                               , 1
                               ,
                               };



int cmp(Stats *stats, uint32_t x, uint32_t y) {
    stats->compares += 1;
    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

uint32_t move(Stats *stats, uint32_t x) {
    stats->moves += 1;
    return x;
}


void shell_sort(Stats *stats, uint32_t *arr, uint32_t length)
{
        uint32_t j;
        uint32_t temp;
        int compare;
        int n = 0;
        uint32_t gap = gaps[n];

        while(gap > 0)
        {
                for(uint32_t i = gap; i < length; i++)
                {
                        j = i;
                        temp = arr[i];
                        compare = cmp(stats, arr[j - gap], temp);
                        while((j >= gap) && (compare == 1))     //use cmp() to do temp < arr[j - gap]
                                {
                                arr[j] = arr[j - gap];                  //use move function
                                move(stats, arr[j]);
                                j -= gap;
                                }
                        arr[j] = temp;
                }
                n++;
                gap = gaps[n];
        }
}


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
