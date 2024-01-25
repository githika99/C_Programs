
/* The ADT List of multiple element*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct list {int data; struct list *next;} list;	//recursive by nature since one of list's members is a list
// represents 1 element of a list. contains that elements value (data), and it points to the next element (pointer next).


int is_empty(const list *l) 		//const is used for redability (just so you know we're not changing the variable);
   {return (l == NULL); } 		// how are we doing l == NULL and not l -> data == NULL
					//bc NULL isn't a value, so as long as smt is in l it is not NULL

void lookup(list *h, const char *key)
   {
   while (h != NULL)
      { 
      if (strcmp(head->key, key) == 0) {           //checks if head-> key and key are the same string
            return head;
      }
      h = h -> next; 			//h now = the next element
      }
      return NULL;
   }

void print_list(list *h, char *title)
   {
   printf("%s\n", title);
   while (h != NULL)
      { printf("%d :", h -> data);
      h = h -> next; 			//h now = the next element
      }
   }

list* create_list(int d)
   {
   list* head = malloc(sizeof(list));
   head -> data = d;
   head -> next = NULL;
   return head;
   }

list* add_to_front(int d, list* h)	//returns a pointer to a list
   {
   list* head = create_list(d);		//creates a pointer named head and makes it equal to a list element of d (it's next is null)
   head ->  next = h;			//next points to h now (last element) bc we're adding to the front of the list
   return head; 
   }

list* array_to_list(int d[], int size)
   {
   list* head = create_list(d[0]);	//creates a list element of data = d[0], next = NULL
   for (int i = 1; i < size; i++)
      head = add_to_front(d[i], head);	
   return head;
   }

//count elements in a list
int recursive_count(list* h)
   {
   if (h -> next == NULL)
      return 1;
   return (1 + recursive_count(h -> next));
   }

int iterative_count(list* h)
   {
   int count = 0;
   while (h -> next != NULL)
      {
      count++;
      h = h -> next; 		// next element of list
      } 
   return ++count;		//add one for the last element who's next -> NULL
   }

//concatonate two lists
void iterative_concat(list* h1, list* h2)
   {
   assert(h1 != NULL);
   while (h1 -> next != NULL)
      h1 = h1 -> next;
   h1-> next = h2;		//once end of list is reached, connect that to h2 
   }

void recursive_concat(list* h1, list* h2)
   {
   assert(h1 != NULL);
   if (h1 -> next == NULL)
      {h1-> next = h2;
       return;}
   else
      recursive_concat(h1 -> next, h2);
   }

//insert an element between two elements
void insert(list *p1,  list *p2, list *q)	//q is element you want to insert between p1 and p2
   {
   assert(p1 -> next == p2);
   p1 -> next = q;
   q -> next = p2;
   }

//delete an element from the list
void delete(list *h, list*d)	//h is an element that comes before d,d is the element you want to delete 
   {
   while (h -> next != d)
      h = h-> next;
   h -> next = d-> next;
   //free your pointer !!!
   }

int main(void)
   {
   int data[10] = {0,1,2,3,4,5,6,7,8,9};
   int data2[4] = {10,11,12,13};
   list *head = array_to_list(data, 10);        //head is a pointer to beginning of the list
   list *head2 = array_to_list(data2, 4);           //head is a pointer to beginning of the list
   list element;
   list *element_head = create_list(-1);

   print_list(head, "multiple element list");
   printf("\niterative count(list) = %d", iterative_count(head));
   printf("\nrecursive count(list) = %d", recursive_count(head));
   
   recursive_concat(head2, head);
   print_list(head2, "\nconcatonated list(head2)");
   //iterative_concat(head2, head);
   //print_list(head2, "\nconcatonated list(head2)");   
   insert(head -> next -> next, head ->next ->next -> next, element_head); 	
   print_list(head, "\n-1 added");
   delete(head, element_head);
   print_list(head, "\n -1 deleted");

   return 0;

   }
