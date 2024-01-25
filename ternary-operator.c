#include <stdio.h>
int main ()
{
   int speed = 0;
   printf("Please enter your speed");
   scanf("%d", &speed);      //reads the input value from previous statement
   speed = (speed < 0)? (0) : (speed <= 65)? (65) : (speed <=70)? (70) : (90);
   switch (speed)
   {  case 65: printf("No ticket"); break;
      case 70: printf("Ticket"); break;
      case 90: printf("Expensive  ticket"); break;
      case 0: printf("Please enter a valid speed");
      // default: _do_smt_;
   }
   return 0;
}
