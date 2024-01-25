#include <stdio.h>
#include <stdint.h>
typedef struct {
   uint64_t moves;
   uint64_t compares;
} Stats;


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

void swap(Stats *stats, uint32_t *x, uint32_t *y) {
    stats->moves += 3;
    uint32_t t = *x;
    *x = *y;
    *y = t;
}


void batcher_sort(Stats *stats, uint32_t *A, uint32_t n);

void comparator (Stats *stats, uint32_t A[], uint32_t x, uint32_t y)
{
        int compare;
        compare = cmp(stats, A[x], A[y]);
        if (compare == 1)                       //use cmp() for A[x] > A[y]
                swap(stats, &A[x], &A[y]);      //use swap() 
}


void batcher_sort(Stats *stats, uint32_t *A, uint32_t n)
{
        if (n == 0)
                return;                 //terminates function

        uint32_t t = n;                        //uint32_t is always 32 bits or 4 bytes
        uint32_t p = 1 << (t - 1);
        uint32_t q;
        uint32_t r;
        uint32_t d;

        while (p > 0)
        {
                q = 1 << (t - 1);
                r = 0;
                d = p;
                while (d > 0)
                {
                        for (uint32_t i = 0; i < (d - n); i++)
                        {
                                if ((i & p) == r)
                                        comparator(stats, A, i, i + d);         //if A[i] > A[i + d], they get swapped
                        }
                        d = q - p;
                        q = q >> 1;
                        r = p;
                }
                p = p >> 1;
        }
}


int main()
{
        Stats batcher_stat;
        batcher_stat.moves = 0;
        batcher_stat.compares = 0;
        uint32_t A[] = {4,1,3,2};
        uint32_t length = 4;
        batcher_sort(&batcher_stat, A, length);

        for (int i = 0; i < length; i++)
                printf("%d\t", A[i]);
        return 0;
}
