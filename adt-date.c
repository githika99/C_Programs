/*This program creates a adt date which includes members month (of enumerate type) and day (of int type) */
#include <stdio.h>

typedef enum month{ jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec} month;
typedef struct date{ month m; int day;} date;

void next_day(date *d)
   {
   d -> day++;
   switch(d -> m)
      { case jan: d -> day %= 32; break;
      case feb: d -> day %= 29; break;
      case mar: d -> day %= 32; break;
      case apr: d -> day %= 31; break;
      case may: d -> day %= 32; break;
      case jun: d -> day %= 31; break;
      case jul: d -> day %= 32; break;
      case aug: d -> day %= 32; break;
      case sep: d -> day %= 31; break;
      case oct: d -> day %= 32; break;
      case nov: d -> day %= 31; break;
      case dec: d -> day %= 32;
      }
   switch(d ->day)
      { case 0: d->day += 1; d -> m += 1; d->m %= 12; }
   }

void print_day(date *d)
   {
   switch(d -> m)
      { case jan: printf("January %d", d -> day); break;
      case feb:  printf("February %d", d -> day); break;
      case mar:  printf("March %d", d -> day); break;
      case apr:  printf("April  %d", d -> day); break;
      case may:  printf("May %d", d -> day); break;
      case jun:  printf("June %d", d -> day); break;
      case jul:  printf("July %d", d -> day); break;
      case aug:  printf("August %d", d -> day); break;
      case sep:  printf("September %d", d -> day); break;
      case oct:  printf("October %d", d -> day); break;
      case nov:  printf("November %d", d -> day); break;
      case dec:  printf("December %d", d -> day); break;
      }
   }

int main (void)
   {
   date today = {0, 1};
   print_day(&today);
   next_day(&today);
   printf("\nthe next day is\n");
   print_day(&today);
   printf("\n");
 
   date today1 = {1, 28};
   print_day(&today1);
   next_day(&today1);
   printf("\nthe next day is\n");
   print_day(&today1);
   printf("\n");

   date today2 = {2, 14};
   print_day(&today2);
   next_day(&today2);
   printf("\nthe next day is\n");
   print_day(&today2);
   printf("\n");

   date today3 = {9, 31};
   print_day(&today3);
   next_day(&today3);
   printf("\nthe next day is\n");
   print_day(&today3);
   printf("\n");

   date today4 = {11, 31};
   print_day(&today4);
   next_day(&today4);
   printf("\nthe next day is\n");
   print_day(&today4);
   printf("\n");
   return 0;
   }
