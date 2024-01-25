/* function creates a fibonacci iterative function and a fibonacci recursive function.
fibonacci numbers are a series. Each number is: F(n) = F(n-2) + F(n-1) */

#include <stdio.h>

void fib_iterative(int n);
int fib_recursive(long f_1_old, long f_1, int times);
int main ()
   {
   int how_many;
   printf("What number would you like in the Fibonacci sequence?");
   scanf("%d", &how_many);
   printf("\niterative\n");
   fib_iterative(how_many);
   printf("\nrecursive\n");
   fib_recursive(0,1,how_many); 

   return 0;
   }
   

void fib_iterative(int n)
   {
   int f = 0,  count = 0;
   int f_1 = 1,  f_2 = 0,  f_1_old = 0;
   for (; count < n; count++)
      {
      printf("%d\t", f_1);
      f = f_1 + f_2;  //old value of sum + new fib number
      f_1_old = f_1;
      f_1 = f;
      f_2 = f_1_old;
      }
   }
      
int fib_recursive(long f_1_old, long f_1, int times)
   {
   if (times == 0)
	return 0;
   else
        {
        printf("%ld\t", f_1);
        return (fib_recursive(f_1, f_1_old + f_1, times - 1));
        }
    } 
