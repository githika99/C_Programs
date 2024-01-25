/*this program merges k sorted linked lists. 
https://leetcode.com/problems/merge-k-sorted-lists/ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

typedef struct node {int data; struct node *prev; struct node *next;} node;	
// prev and next are pointers of type node 

int is_empty(node *l)
   {return(l == NULL);}

void print_list(node *h, char *title)
   {
   int i = 0;
   printf("\n%s\t", title);
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

node* add_to_back(node *h, int d)   //h is the last element in the list. new is the element you want to add to the back
   {
   assert(h -> next == NULL);
   node* new = create_list(d);
   h -> next = new;
   new -> prev = h;
   new -> next = NULL;
   return new;                  //new last element
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

//delete first element of list
node* delete_first (node *h)
   {
   assert(h -> prev == NULL);
   if (h -> next != NULL)
      {
        h -> next -> prev = NULL;
        return h -> next;
      }
   return NULL;
   }

node* array_to_list(int d[], int size)
   {
   node* head = create_list(d[0]);	//creates a list element of data = d[0], next = NULL
   node *use = head;
   for (int i = 1; i < size; i++)
      use = add_to_back(use, d[i]);	
   return head;
   }

node* merge_sort(node * h1, node * k1)    
   {
   node * original = NULL; //initialize original
    if (h1 -> data <= k1-> data)
        {original = create_list(h1 -> data);
        h1 = delete_first(h1);}
    else
        {original = create_list(k1 -> data);
        k1 = delete_first(k1);}
      
   node *result = original;
   while (h1 != NULL && k1 != NULL)
      {
        if (h1 -> data <= k1-> data)
           {
            result = add_to_back(result, h1 -> data);
           h1 = delete_first(h1);}
        else
           {
            result = add_to_back(result, k1 -> data);
            k1 = delete_first(k1);}
      }
   while (h1 != NULL)
      {
       result = add_to_back(result, h1 -> data);
       h1 = delete_first(h1);
      }

   while (k1 != NULL)
      {
        result = add_to_back(result, k1 -> data);
        k1 = delete_first(k1);
      }
    return original;
   }



int main ()
   {   
   int d1[] = {1,2,5};
   node *h1 = array_to_list(d1, 3);

   int d2[] = {1,3,4};
   node *h2 = array_to_list(d2, 3);

   int d3[] = {2,6};
   node *h3 = array_to_list(d3, 2);

   //array of pointers to my lists

   node* my_array[] = {h1, h2, h3};
   int SIZE = 3;


   for (int i = 1; i < SIZE; i++)
      {
      my_array[i] = merge_sort(my_array[i - 1], my_array[i]);
      print_list(my_array[i], "\nresult\n");
      }
   
   return 0;
   }