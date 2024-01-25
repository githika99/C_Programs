#include <stdio.h>

void swap (int *i, int *j);

int main ()
   {
   int a = 7, b = 19;
   printf("a is %d, b is %d\n", a, b);
   swap(&a, &b);	//pointers of a and b are passed as arguments
   printf("a is now %d, b is now %d\n", a, b);   
   return 0;
   }


void swap (int *i, int *j)	//takes pointers as arguments
   {
   int temp = *i; 	//*i is dereferenced i
   *i = *j;
   *j = temp;
   }
