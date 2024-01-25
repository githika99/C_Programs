/*This program takes an input as from 0 to 1 and prints out the sine of that value*/

#include <stdio.h>
#include <math.h>

int main(void) {
 double x;
 printf("Please enter a number between 0 and 1:\n");
 scanf("%lf", &x);
 printf("The sine of %lf is %lf \n", x, sin(x));

 return 0;
}
