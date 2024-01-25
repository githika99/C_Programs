/* The ADT List of one element*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct list {int data; struct list *next;} list;	//recursive by nature since one of list's members is a list
// represents 1 element of a list. contains that elements value (data), and it points to the next element (pointer next).


int is_empty(const list *l) 		//const is used for redability (just so you know we're not changing the variable);
   {return (l == NULL); } 		// how are we doing l == NULL and not l -> data == NULL
					//bc NULL isn't a value, so as long as smt is in l it is not NULL
void print_list(list *h, char *title)
   {
   printf("%s\n", title);
   while (h != NULL)
      { printf("%d :", h -> data);
      h = h -> next; 			//h now = the next element
      }
   }


int main(void)
   {
   list list_of_int;
   list *head = NULL; 		//head is a pointer to beginning of the list
   head = malloc(sizeof(list)); //assgining where head will look to in memory
   printf("sizeof(list) = %lu\n", sizeof(list)); 	//sizeof(x) returns the # of bytes in x as an unsigned long
   
   head -> data = 5; 		//head points to a list
   head -> next = NULL;		//NULL signifies end of list
   
   print_list(head, "single element list");
   printf("\n\n");
   return 0;

   }
