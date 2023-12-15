#include <stdio.h>
#include "mathlib.h"

static int euler_terms;

double pi_euler()
{
   double sum = 0;
   double k = 1.0;
   double current = 1;
   while (current > EPSILON)
   {
   current = (1/(k*k));
   sum += current;
   k++;
   }
   sum *= 6;
   euler_terms = k - 1;
   return sqrt_newton(sum);		//calls sqrt_newton() in newton.c
}

int pi_euler_terms()
{
return euler_terms;
}

/*
int main (void)
{
printf("%.15f", pi_euler());
printf("\tterms used: %d", pi_euler_terms());
return 0;
}
*/
