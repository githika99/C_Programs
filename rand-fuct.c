

#include <stdio.h>
#include <stdlib.h>
#include <time.h>




void rand_range(int array[])
   {
   //array is an array of size 70
   //srand ( time(NULL) );
   for (int i = 0; i < 10; i++)		//picks 10 random numbers from the array of 70 items
      printf("%d\t", (array[rand() % 70]));
   }


int main (void)
   {
   int array1[70];

   for (int i = 0; i < 70; i++)
      array1[i] = i;

   srand ( time(0) );   
   for (int i = 0; i < 5; i++) 		//calls rand_range 5 times
      {
      printf("\nIteration %d\n", i);
      rand_range(array1);
      }
   return 0;
   }
