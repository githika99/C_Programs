#include <stdio.h>
#include "mathlib.h"

static int iterations = 0;

double sqrt_newton(double x)
   {
   iterations = 0;
   double z = 0.0;
   double root  = 1.0;
   while(absolute( root - z ) > EPSILON)
      {
      z = root;
      root  = 0.5 * (z + x / z);
      iterations++;
      }
   return root;
   }

int sqrt_newton_iters()
{
return iterations;
}

/*
int main ()
{
	for (double i = 0; i <= 10; i += .01)
	{iterations = 0;
        printf("\nsqrt_newton(%f) = %.15f, terms used %d", i, sqrt_newton(i), sqrt_newton_iters() );
        }
	return 0;
}
*/
