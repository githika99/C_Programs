#include <stdio.h>

extern int my_glbl_var; //global variable
int my_glbl_var = 9;

int increment();

int main(void)
   {
   for (int i = 0; i <= 10; i++)
      {
      printf("c is now = %d\n", increment());
      }
   printf("global variable is %d\n", my_glbl_var);
   return 0;
   }

int increment()
   {
   static int c = 0;
   c++;
   return c;
   }

