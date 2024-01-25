#include<stdio.h>
#include<math.h> /* has  sin(), abs(), and fabs() */
int main(void)
{ 
   double value;
   int sign;
   printf("Please enter a value: ");
   scanf("%lf", &value);   
   value = sin(value);
   sign  = (value < 0)? (-1) : (1) ;
   switch (sign)
   {
   case 1: ; break; 
   case -1: value = value *-1;
   }
   printf("%lf", value);

   return 0;
}
