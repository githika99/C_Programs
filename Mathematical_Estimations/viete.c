#include <stdio.h>
#include "mathlib.h"

static int v_terms = 0;

double pi_viete()
{
   double k = 1;
   double previous = 0;
   double current = sqrt_newton(2.0); 
   double sum = current;
  // printf("epsilon is %.15f", EPSILON);
   while (absolute((current / 2.0) - 1) > EPSILON)
   {
  // printf("\n\nprevious is %.15f", previous);
  // printf("\ncurrent is %.15f", current);
  // printf("\ncurrent/2.0 is %.15f", current/2.0);
  // printf("\ncurrent/2.0 -1 is %.15f", (current/2.0) - 1);
   previous = current;
   current = (sqrt_newton(2.0 + previous));
   if (absolute((current / 2.0) - 1) > EPSILON)
      sum *= current/2.0;
   k++;
   }

   sum *= 1.0/4.0;
   sum = 1.0/(sum);
   v_terms = k -1;
   return sum;
}

int pi_viete_factors()
{
return v_terms;
}

/*
int main()
{
printf("\npi is %.15f", pi_viete());
printf("\nterms used is %d", pi_viete_factors());
	return 0;
}
*/
