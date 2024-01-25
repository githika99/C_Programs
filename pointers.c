#include <stdio.h>

int main (void)
   {
   const int SIZE = 10;
   int my_integer = 17;
   double my_array[SIZE] = {1};
   int *ptr = &my_integer;

   char str[] = "abcd";
   
   printf("%d is stored at %p\n my_array starts at %p\n my_array[4] aka the 5th element is stored at %p\n the last element in the array is stored at %p",*ptr, ptr,  my_array, my_array + 5, my_array + 10); 
   
   //my_array is  address my_array starts at AKA address of my_array[0]
   //my_array + 2 is address of my_array[2]
   //you get that by doing: base address + (# of bytes for type * # of elements)
   // my_array[2] = my_array[0] + (8 * 2) 		//bc there are 8 bytes in a double 

   return 0;
   }
