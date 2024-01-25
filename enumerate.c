/*This program tests the functionality of user defined type enumerate.
Enumerate is a special type of data type defined by the user. It consists of constant (consecutive) 
integers given names by the user. Naming these integer values makes the code easy to read.
Enumerate is based off of the integer type.
You can create any data type in C.   */

#include <stdio.h>

enum day {sun,mon,tue,wed,thu,fri,sat}; 	//declare type (type name is enum day)
//         0 , 1 , 2 , 3 , 4 , 5 , 6
void print_day(enum day d)
   {
   switch (d)
      {
      case sun: printf("Sunday\n"); break;
      case mon: printf("Monday\n"); break;
      case tue: printf("Tuesday\n"); break;
      case wed: printf("Wednesday\n"); break;
      case thu: printf("Thursday\n"); break;
      case fri: printf("Friday\n"); break;
      case sat: printf("Saturday\n"); break;
      default: printf("There is an error. You entered: %dy\n", d); break;
      }
   }

enum day next_day(enum day d)		//enum day is the return type of the function next_day
   {
   return (d + 1 % 7);			// once we get to 6, we go to 0 rather than 7
   }					//return type appears to be an integer, but it is an enum day
   					//since every variable in enum corresponds to a # 0-6

enum day yesterday(enum day d)          
   {
   if (d == 0)
      d = 7;
   return (d - 1);                
   }

int main(void)
   {
   enum day today = wed;
   print_day(today);
   print_day(2); //should be tuesday
   print_day(next_day(today));  //should be thursday
   //value of today did not change
   print_day(yesterday(sun)); //should be saturday
   return 0;
   }

