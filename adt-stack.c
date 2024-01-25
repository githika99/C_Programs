/* Abstract Data Type (ADT) stack. */

#include <stdio.h>
#include <ctype.h>
#define MAX_LEN 1000
#define EMPTY -1
#define FULL (MAX_LEN - 1)  

typedef struct  stack
   { char s[MAX_LEN]; 
     int top;
   } stack;

void push(char c, stack *stk)	//takes pointer of stack as argument. stack is an array, so we could also do stack stk s[]
   {
   stk -> top ++;		//stk -> top accesses the variable top for the stack instance stk. 
   stk -> s[stk -> top] = c;    //stk -> s, accesses the stack for the instance stk. 
   }				//then, we assign the last element of the stack to c

char pop(stack *stk)
   {
   return (stk -> s[stk -> top--]); 	//returns the character at top of stack and then subtracts top by 1
   }

void reset(stack *stk)
   {
   stk -> top = EMPTY;		//can be -1 cause if you were to push anything, you would add 1 to the top first
   }				//-1 is also useful to check if stack is empty incase you want to pop smt

int top(stack *stk) 		//returns character at top of stack without poping it
   {
   return (stk -> s[stk -> top]); 
   }

int isempty(stack *stk)
   {
   return (stk -> top == EMPTY);	//returns 1 if it is empty, 0 if it is not empty
   }

int isfull(stack *stk)
   {
   return (stk -> top == FULL);		//returns 1 if it is full, 0 if it is not full
   }

int main (void)
   {
   stack stack_of_char;
   char *str = "reverse this !";
   
   reset(&stack_of_char);
   printf("original string is: %s\n", str);
   
   int i=0; 
   while (str[i] != '\0')
      {
      printf("%c\n", str[i]);
      push(str[i++], &stack_of_char);
      }

   //pop each element from the stack and store it in a new string str_reversed
   char str_reversed[20];
   i = 0;
   while(!isempty(&stack_of_char) && i < 20)
      {
      str_reversed[i++] = pop(&stack_of_char);
      }

   printf("the reversed string is: %s", str_reversed);

   return 0;
   }
