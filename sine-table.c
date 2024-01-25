#include <stdio.h>
#include <math.h>
int main ()
{
   for (double i = 0; i <= 1; i = i + .10)
   {
      printf("sin(%lf) = %lf. cos(%lf) = %lf\n", i, sin(i), i, cos(i));
   }
   return 0;
}
