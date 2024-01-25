/* Bubble sort is O(N*N) complexity, even though I coded a more efficent version. In the worst case, it could take up to O(N*N) */
#include <stdio.h>

void swap (int *i, int *j)	//takes pointers as arguments
   {
   int temp = *i; 	//*i is dereferenced i
   *i = *j;
   *j = temp;
   }

void print_array(int array[], int SIZE)
   {
   for (int i = 0; i < SIZE; i++)
      { printf("%d\t", array[i]);
      }
   printf("\n");
   } 

void bubble(int array[], int SIZE);

int main (void)
   {
   const int SIZE = 5;
   int my_grades[SIZE] = {70,60,40,50,100};
   printf("initially, my_grades is ");
   print_array(my_grades, SIZE);
   bubble(my_grades, SIZE);
   printf("bubble sorted list is ");
   print_array(my_grades, SIZE);
   return 0;
   }

void bubble(int array[], int SIZE)
   {
   int num_of_swaps = 0;
   int bubble_loop = 0;
   for (int i = 0; i < SIZE; i++)
      {
      
      num_of_swaps = 0; 	//reset before each bubble sort
      //bubble sort
      bubble_loop++;
      for (int j = 1; j < SIZE; j++)
         {
         if (array[j] < array[j-1])	 //if 0, 1 1 is less than 0, swap them
             {
             num_of_swaps = num_of_swaps + 1;
             swap(&array[j], &array[j-1]);
             }
         }
      printf("after running bubble sort %d times, the array is:  ", bubble_loop);
      print_array(array, SIZE);
      //after bubble sort
      if (num_of_swaps == 0)
         break; 

      }
    printf("\nbubble sort was run %d times\n", bubble_loop);
   }









