
/* Merge sort is O(N log(N)) complexity.
Merge sort takes two sorted lists and creates one sorted list out of the elements from those two. */
#include <stdio.h>

void print_array(int array[], int SIZE)
   {
   for (int i = 0; i < SIZE; i++)
      { printf("%d\t", array[i]);
      }
   printf("\n");
   } 

void merge_sort(int array1[], int SIZE1, int array2[], int SIZE2, int result[]);

void merge_an_array(int key[], int size)	//call merge_sort w lists of 1 element each, then 2 elements, then 4... until the end of list is reached
   {
   int j, k;
   int result[size];
   for (k = 1; k < size; k = k * 2)
      {
      for (j = 0; j < size - k; j = j + 2*k)
         merge_sort(key + j, k, key + j + k, k, result + j);					//key + j is the memory address of key + j elements
      for (j = 0; j < size; j++)
         key[j] = result[j];

      } 

   }

void merge_sort(int array1[], int SIZE1, int array2[], int SIZE2, int result[])    //when arrays are passed as arguments, their memory location is passed
   { 										   //this is why we can edit the array in the funct and it gets permanently changed
										   //bc we are directly changing what is in the memory address
										   // not an instance of the array
   const int SIZEr = SIZE1 + SIZE2;

   int i = 0, j = 0, c = 0;     //i is index for array1. it increments up to SIZE1. j is index for array2. it increments up to SIZE2.
   while (i < SIZE1 && j < SIZE2 )      //once one pile gets fully added to the result pile, its increment variable will equal the size of the array - 1
      {
      if (array1[i] < array2[j])
         result[c++] = array1[i++];     //add the element to the result array. increment c so that the next time a # gets added its to the next position.
      else
         result[c++] = array2[j++];
      }
   while (i < SIZE1)
      {
      result[c++] = array1[i++];
      }
   while (j < SIZE2)
      {
      result[c++] = array2[j++];
      }

   printf("merge sorted list is\n");
   print_array(result, SIZEr);
   }

int main (void)
   {
   const int SIZE = 8;
   int my_grades[SIZE] = {70,60,20,90,40,50,100,90};   //list has to have size of a 2 power
   printf("initially, my_grades is ");
   print_array(my_grades, SIZE);
   merge_an_array(my_grades, SIZE);
   printf("\nMerge sort finished........\n");
   print_array(my_grades, SIZE);   
   return 0;
   }











