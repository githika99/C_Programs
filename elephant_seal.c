/*This program take a file as input (run it using a.out <file.txt). it can only be used for a file with numbers seperated by spaces that is 1000 elements long. it reads these numbers into an array and then computes the average of all the elements in the file. */
#include <stdio.h>

void print_array(int array[], int SIZE)
   {
   for (int i = 0; i < SIZE; i++)
      { printf("%d\t", array[i]);
      }
   printf("\n");
   }

double average(int key[],int size)
   {
   double avg = 0.0;
   for (int i = 0; i < size; i++)
      avg += key[i];
   avg = avg / size;
   return avg;
   }

int main(void)
{
   int c, d;
   int size = 1000;	//for the text file elephant_seal.txt, there are 1000 entries
   int current_num = 0;
   /*
   // I was trying to make a loop to find the number of #s in the file to create an array. But, the problem is that you cannot have two loops that use getchar() (unless there is some way to reset getchar()). This is because after one loop using getchar() is executed, the next character is EOF, since the file has been fully read. Thus, we cannot restart the getchar() to the beginning of the file.
   for (; (d = getchar()) != EOF;)
   {
      printf("in first loop\n");
      if (d == ' ')
         size += 1;               
   }
   */
   
   int array[size];
   int counter = 0;

   //printf("right before entering for loop, size = %d", size);

   for (; (c = getchar()) != EOF;)
   {  
      // printf("we are entering the second for loop\n");
      if (c == ' '){
         array[counter] = current_num;
         current_num = 0;
         counter += 1;
         //printf("\n\n");
         }
      else if (c >= '0' && c <= '9')
         current_num = (current_num*10)  + (c-48);
         //printf("current_num is now %d, c is %d\n", current_num, c);
        
   }
   
   //print_array(array, size);
   printf("\nThe avergae of the array is: %lf", average(array, size));
   return 0; 

}

