#include <stdio.h>

int main(void) {

char c = 'a';
printf("this is the ASCII value of c: %d \n", c);
printf("this rings a bell?? %c\n", '\a');
printf("this is the character value of c: %c \n", c);
printf("this rings a bell?? %c\n", '\a');
printf("i can consecutively add 1 to c: %c %c %c.\n These are ASCII values %d %d %d\n", c, c+1, c+2, c, c+1, c+2);
printf("this rings a bell?? %c\n", '\a');
return 0;
}
