#include <stdio.h>
#include "mathlib.h"
// they used 11 terms and got accuracy to 15 digits of pi.
static int b_terms = 0;

double pi_bbp()
{
   double sum = 0;
   double k = 0;
   double power = 1;
   double current = 1;
   while (current > EPSILON)
   {
   power = 1;
   for (int temp = 1; temp <= k; temp++)
	   power*= 16;
   current = (1.0/power) * (k*(120*k + 151) + 47) / (k*(k*(k*(512*k + 1024) + 712) + 194) + 15);
   sum += current;
   k++;
   }
   b_terms = k;
   return sum;
}

int pi_bbp_terms()
{
return b_terms;
}

/*
//for testing purposes. remove for submission.
int main (void)
{
printf("%.15f", pi_bbp());
printf("\t terms used: %d", pi_bbp_terms());
return 0;
}
*/

