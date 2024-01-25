/*This program creates a doubly linked list of random numbers from 0 to 49. 
then it sorts the list using bubble sort. 
finally it removes duplicates of the list. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

typedef struct node {int data; struct node *prev; struct node *next;} node;	
// prev and next are pointers of type node 
int SIZE = 200;

void print_list(node *h, char *title)
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

node* create_list(int d)
   {
   node* head = malloc(sizeof(node));
   head -> data = d;
   head -> next = NULL;
   head -> prev = NULL;
   return head;
   }

node* add_to_front(int d, node* h)	//returns a pointer to a list
   {
   node* head = create_list(d);		//creates a pointer named head and makes it equal to a list element of d (it's next is null)
   head ->  next = h;			//next points to h now (last element) bc we're adding to the front of the list
   head -> prev = NULL;         //since it is first element
   h -> prev = head;
   return head; 
   }

void add_to_back(node *h, node* new)   //h is the last element in the list. new is the element you want to add to the back
   {
   assert(h -> next == NULL);
   h -> next = new;
   new -> prev = h;
   new -> next = NULL;
   }

//insert an element between two elements
node* insert(node *p1,  node *p2, node *q)	//q is element you want to insert between p1 and p2
   {
   assert(p1 -> next == p2 && p2 -> prev == p1);
   p1 -> next = q;
   q -> next = p2;
   p2 -> prev = q;
   q -> prev = p1;
   return p1;
   }

//delete an element from the list
void delete(node *h, node*d)	//h is an element that comes before d,d is the element you want to delete 
   {
   while (h -> next != d)
      h = h-> next;
   //if d is the last element
   if (d -> next == NULL)
      {//printf("\n%d is the last element", d -> data);
      h-> next = NULL;
      d -> prev = NULL;
      }
   else
      {
        h -> next = d-> next;
        d -> next -> prev = h;
      }
   }

node* bubble_sort(node *original)
   {
   node *head;
   node *next_d;
   int swaps_made;
   int num_loops;
   for (int j = 1; j < SIZE; j++)
    {
        head = original;
        next_d = head -> next;
        num_loops++;
        swaps_made = 0;
        for (int i = 0; i < SIZE - j ; i++)
            {
            num_loops++;
            if (head -> data > next_d -> data)
                {
                //printf("\n head is: %d", head -> data);
                swaps_made++;
                if (head -> prev == NULL)     //head is first element
                    {
                        //printf("\nswapped %d and %d", head -> data, next_d -> data );
                        delete(original, (next_d));
                        original = add_to_front(next_d -> data, original);
                        head = original;
                        //print_list(original, "\n");
                    }
                else if (next_d -> next == NULL)      //head is 2nd to last element
                    {
                    //printf("\nswapped %d and %d", head -> data, next_d -> data );
                    delete(head -> prev, head); 
                    add_to_back(next_d, head);
                    //print_list(original, "\n");
                    break;
                    }
                else
                {
                //printf("\nswapped %d and %d", head -> data, next_d -> data );
                delete(head -> prev, head); 
                head = insert(next_d, (next_d -> next), head);
                //print_list(original, "\n");
                } 
                }
            head = head -> next;
            next_d = head -> next;
            }
    if (swaps_made == 0)
       break;
    }
    //printf("\nNum Loops: %d\n", num_loops);
    return original;
   }

node* remove_duplicate(node *original)
   {
   node *h = original;
   node *next_d = h-> next;
   while (next_d != NULL)
      {
      while (1 == 1)
        {   
            if (h -> data == next_d -> data)
                {delete(h, next_d);
                if (h -> next == NULL)
                   break;
                else
                    next_d = h -> next;}
            else
               break;
        }
      if (h -> next == NULL)
         break;
      else
          {
          h = h -> next;
          next_d = h -> next;
          }
      }
    return original;
   }

int main()
   {
   srand ( time(NULL) );
   node *original = create_list(rand() % 50);
   for (int i = 0; i < SIZE - 1; i++)
        {
        original = add_to_front((rand() % 50), original);
        }
    print_list(original, "List before sorting:");
    original = bubble_sort(original);
    print_list(original, "\n List after bubble sort:");
    original = remove_duplicate(original);
    print_list(original, "\n ....Duplicates removed...");
   }



