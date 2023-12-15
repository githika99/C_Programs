#include <stdio.h>
#include "mathlib.h"

static int m_terms = 0;

double pi_madhava()
{
   double sum = 1;
   int k = 1;
   double power = 1;
   double current = 1;
   while (absolute(current) > EPSILON)
   {
   //write loop to make power
    power = 1;
   for (int temp = 1; temp <= k; temp++)
	   power *=(-3);
   current = 1/((2*k + 1)*power);
   sum += current;
   k++;

   }
   m_terms = k;
   
   return sum*sqrt_newton(12);	//calls sqrt_newton() from newton.c
}


int pi_madhava_terms()
{
   return m_terms;
}

/*
//for testing purposes only. remove for submission.
int main (void)
{
   printf("pi_madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI, M_PI - pi_madhava());
   printf("number of terms used is %d", pi_madhava_terms());   

   return 0;
}
*/
