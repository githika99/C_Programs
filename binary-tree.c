/* writes a program to make a binary tree */

#include <stdio.h>
#include <stdlib.h>

typedef int DATA; 	//to be simple, our tree can only have characters

typedef struct node {DATA d; struct node *left; struct node *right;} NODE;	//pointer to left node, pointer to right node

typedef NODE *BTREE; 	//creates a pointer of NODE type
			//BTREE b; now does what: node *b; would have done

//prints tree in order 
void inorder(BTREE root)	//takes a pointer to the root of a tree as argument
   {
   if (root != NULL)
      {
      inorder(root -> left);
      printf("%d", root -> d);   //print node
      inorder(root -> right);
      }
   }

void preorder(BTREE root)	//takes a pointer to the root of a tree as argument
   {
   if (root != NULL)
      {
      printf("%d", root -> d);   //print node
      preorder(root -> left);
      preorder(root -> right);
      }
   }

void postorder(BTREE root)	//takes a pointer to the root of a tree as argument
   {
   if (root != NULL)
      {
      postorder(root -> left);
      postorder(root -> right);
      printf("%d", root -> d);   //print node
      }
   }

void print_tree(BTREE root, int spaces) //traverses tree in reverse of inorder
   {
   if (root != NULL)
   {
      print_tree(root -> right, spaces + 1);
      for (int i = 0; i < spaces; i++)
         printf("     ");  
      printf("%d\n\n", root -> d);
      print_tree(root -> left, spaces + 1);
   }
   }

/*
int max_depth(BTREE root)
   if (root -> right == NULL && root -> left == NULL)
      return 1;
   else if (root -> right != NULL && root -> left == NULL)
      return (1 + max_depth(root -> right));
   else if (root -> right == NULL && root -> left != NULL)
      return (1 + max_depth(root -> left));
   else
      return 1 + max_depth(root -> right) + max_depth(root -> right);
*/

//allocates memory space for a new node, returns a pointer to this node
BTREE new_node()
   {return(malloc(sizeof(NODE)));}     //NODE is a data type of fixed size

//create a new node
BTREE init_node(DATA d1, BTREE p1, BTREE p2)
   {
   BTREE t;
   t = new_node();               //t is a pointer to a new node
   t -> d = d1;
   t -> left = p1;
   t -> right = p2;
   return t;                     //return pointer to node
   }

BTREE create_tree(DATA a[], int i, int size)
   {
   if (i >= size)
      return NULL;
   
   //printf("\ni is %d. a[i] is %c", i, a[i]);
   //printf("\ncalling: init_node(  %c,  create_tree(a, %d, size),  create_tree(a, %d, size)\n", a[i], 2*i + 1, 2*i + 2);
   return(  init_node(  a[i],  create_tree(a, 2*i +1, size),  create_tree(a, 2*i +2, size)  )  );
   }

   
int main()
   {
   int d[] = {1, 2, 3, 4, 5,6,7};
   BTREE b;
   b = create_tree(d, 0, 7);
   inorder(b);
   printf("\n");
   preorder(b);
   printf("\n");
   postorder(b);
   printf("\n");
   print_tree(b, 0);
   
   return 0;
   }
