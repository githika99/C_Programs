/*this program creates a list of 100 random elements, then sorts them using bubble sort.
The output is the original list, the number of times a loop was ran during bubble sort, 
and finally the sorted list. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

typedef struct list {int data; struct list *next;} list;	
int SIZE = 5;

void print_list(list *h, char *title)
   {
   int i = 0;
   printf("%s\n", title);
   while (h != NULL)
      {
      if (i++ % 5 == 0)
         printf("\n");
      printf("%d :", h -> data);
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

void add_to_back(list *h, list* new)   //h is the last element in the list. new is the element you want to add to the back
   {
   assert(h -> next == NULL);
   h -> next = new;
   new -> next = NULL;
   }

//insert an element between two elements
list* insert(list *p1,  list *p2, list *q)	//q is element you want to insert between p1 and p2
   {
   assert(p1 -> next == p2);
   p1 -> next = q;
   q -> next = p2;
   return p1;
   }

//delete an element from the list
void delete(list *h, list*d)	//h is an element that comes before d,d is the element you want to delete 
   {
   while (h -> next != d)
      h = h-> next;
   h -> next = d-> next;
   }

void bubble_sort(list *original)
    {
    list *temp;
    list *head = NULL;
    int swaps_made = 0;
    int total_loops = 0;

    for (int j = 1; j < SIZE; j++)
    {       total_loops++;
            swaps_made = 0;
            //printf("\n\nnew iteration of outer loop: %d\n\n", j);
            //first switch
            if ((original -> data) > (original -> next -> data))
            {   total_loops++;
                temp = original -> next;
                //printf("\nswapped %d and %d", original -> data, original -> next -> data );
                delete(original, (original -> next));
                original = add_to_front(temp -> data, original);
                //print_list(original, " ");
                swaps_made++;
            }
            if (j == SIZE -1)   //last outer loop iteration, only first two numbers need to be compared
               break;
            
            //middle switches
            head = original -> next;
            for (int i = 1; i < SIZE - j; i++)
            {   total_loops++;
                temp = head -> next;
                if ((head -> data) > (temp -> data))
                { //printf("\nswapped %d and %d", head -> data, temp -> data );
                delete(original, head);
                if (temp -> next == NULL)
                   add_to_back(temp, head);
                else
                   head = insert((temp), (temp -> next), head);
                
                //print_list(original, " ");
                swaps_made++;
                }
                head = head -> next;
            }

            if (swaps_made == 0)    //0 swaps made means list is already sorted
               break;
    }
    printf("\n\ntotal # of loops done is: %d\n", total_loops);
    }

int main()
    {
    srand ( time(NULL) );
    list *original = create_list(rand() % 100);
    for (int i = 0; i < SIZE - 1 ; i++)
        {
        original = add_to_front((rand() % 100), original);
        }
    print_list(original, "List before sorting:");
    bubble_sort(original);
    print_list(original, "\nList after sorting:");
    
    }
