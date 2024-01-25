#include <stdio.h>
int main(void)
{
   int blanks = 0, tabs = 0, digits = 0, letters = 0, total_chars = 0;
   int c;
   int current_num = 0;
   for (; (c = getchar()) != EOF; total_chars++)
   {
      if (c == ' '){
         printf("%d", current_num);
         printf("\t");
         current_num = 0;
         ++blanks;}
      else if (c == '	')
	 ++tabs;
      else if (c >= '0' && c <= '9'){
         current_num = current_num * 10 + (c-48);
         ++digits;
         }
      else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
         ++letters;
   };

   printf("\nblanks = %d, tabs = %d,  digits = %d, letters = %d, total_chars = %d", blanks, tabs, digits, letters, total_chars);

   return 0; 

}
