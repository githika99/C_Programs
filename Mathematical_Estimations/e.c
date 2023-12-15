#include <stdio.h>
#include "mathlib.h"

static int terms_e = 0;

//1/k! approaches 0 as k grows larger

double e()
{
   double k = 1;
   double current;
   double previous = 1.0;
   double sum = previous;
   while ( previous > EPSILON)
   {
   current = (1.0/k) * previous;
   previous = current; 
   sum += current;
   k++;
   }

terms_e = k;
return sum;
}

int e_terms()
{
return terms_e;
}

/*
//for testing only. remove for submission.
int main (void)
{
printf("e() is %.15f, M_E is %.15f, diff is %.15f", e(), M_E, M_E - e());
printf("terms used: %d", e_terms());


return 0;
}
*/
