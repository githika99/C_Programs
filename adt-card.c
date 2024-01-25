/* This program creates an adt for a card with members pips (card #) and suit. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum suit{c, h, d, s} suit;
typedef struct card {short pips; suit s;} card;
// pips can be anywhere from 1-13; suit can  be 'c', 'h', 'd', 's'
card null_card = {-1,-1};

void print_card (card *my_card)
   {
   switch(my_card -> s) //looking at the suit
      { case c: printf("%d of Clubs\n", my_card-> pips); break;
       case d: printf("%d of Diamonds\n", my_card-> pips);break;
      case h: printf("%d of Hearts\n", my_card-> pips);break;
      case s: printf("%d of Spades\n", my_card-> pips);
      }
   }

void shuffle_deck(card deck[])		//we only need pointers to look at the members of the adt
   {					//if we're looking at the whole adt, we don't need pointers
   //srand ( time(NULL) );
   card temp;
   int new_position;
   for (int i = 0; i < 52; i++)
     {
     temp = deck[i];
     new_position = rand() % 52;
     deck[i] = deck[new_position];
     deck[new_position] = temp;
     }     
   }

void deal_5_card_hand(card deck[], card hand[])
   {
   //card hand[] is an array of 5 cards
   //srand ( time(0) );
   for (int i = 0; i < 5; i++)
      { hand[i]  = deck[rand() % 52];}		//we'll see if this assignment works. otherwise we use pointers
   }

int eq_card(card *c1, card *c2)
   {
   if (c1->s == c2->s && c1->pips == c2->pips)
      return 1;
   else
      return 0;
   }

void num_of_pairs(card hand[], int pairs[])
   {
   //pairs is an array with 3 elements of ints. 
   //the first int is the number of pairs in the hand. 
   //the second int is the number of 3 of a kinds in a hand. the third int is the number of 4 of a kinds in a hand.
   //pairs = {0,0,0};
   pairs[0] = 0; pairs[1] = 0; pairs[2] = 0;
   card pair1 = {-1 , -1};
   card pair2 = {-1, -1};
   card current_card;
   int matches = 0, three_of_a_kind = 0, four_pair = 0;
   for (int i = 0; i < 4; i++)
      {
      current_card = hand[i];
      matches = 0; three_of_a_kind = 0; four_pair = 0;
      for (int j = i + 1 ; j < 5; j++)
         {
         if (eq_card(&current_card, &pair1) || eq_card(&current_card, &pair2))
 	    break; //break inner loop if card is already in a pair
         else if (eq_card(&current_card, &hand[j])  && matches == 0 && three_of_a_kind == 0)
            matches++;
         else if (eq_card(&current_card, &hand[j]) && matches == 1)
            { matches = 0; three_of_a_kind = 1; }
         else if (eq_card(&current_card, &hand[j]) && matches == 0 && three_of_a_kind == 1)
            {three_of_a_kind = 0; four_pair = 1; break;}	//break out of inner loop
         }
      if (matches == 1)
          pairs[0] += 1; 
      else if (three_of_a_kind == 1)
          pairs[1] +=1;
      else if (four_pair == 1)
          pairs[2] += 1;
      if ((matches == 1 || three_of_a_kind == 1 || four_pair == 1) && eq_card(&pair1,&null_card))
          pair1 = hand[i];
      else if (matches == 1 || three_of_a_kind == 1 || four_pair == 1)
          pair2 = hand[i];
      }   
   }

void which_hand(int p[], int *no_pair, int *one_pair, int *two_pair, int *three_of_a_kind, int *four_of_a_kind, int *full_house)
   {
   if (p[0] == 0 && p[1] == 0 && p[2] == 0)   
      *no_pair+= 1; 
   else if (p[0] == 1 && p[1] == 0 && p[2] == 0)
      *one_pair+= 1;
   else if (p[0] == 2 && p[1] == 0 && p[2] == 0)
      *two_pair+= 1;
   else if (p[0] == 0 && p[1] == 1 && p[2] == 0)
      *three_of_a_kind+= 1;
   else if (p[0] == 0 && p[1] == 0 && p[2] == 1)
      *four_of_a_kind+= 1;
   else if (p[0] == 1 && p[1] == 1 && p[2] == 0)
      *full_house+= 1;
   }

int main (void)
   {
   //make 52 cards
   srand ( time(0) );
   card deck[52];			//array of card type, with 52 elements
   card hand[5];
   int pairs[3] = {0, 0, 0};
   double total_hands = 1000000.0;
   int no_pair = 0;
   int one_pair = 0;
   int two_pair = 0;
   int three_of_a_kind = 0;
   int four_of_a_kind = 0;
   int full_house = 0;
   card hand1[5] = { {1,0}, {5,2}, {1,0}, {9,3}, {4,2}  };
   int a;   

   //create a deck
   short pips_num = 0;
   short suit_num = 0;
   card my_card;
   card *ptr_to_card;
   for (int i = 0; i < 52; i++)
      {  srand ( time(NULL) );
      ptr_to_card = &my_card;	//ptr_to_card now points to the memory address of my_card
      ptr_to_card -> pips = (pips_num++  % 13) + 1;
      if (ptr_to_card-> pips == 1)	// we have all cards 1-13 for that suit
      	ptr_to_card -> s = (suit_num++  % 4);
      deck[i] = my_card;	//makes a deck 
      //print_card(&deck[i]);
      }

   //shuffle deck
   //printf("Now we shuffle the cards\n\n");
   shuffle_deck(deck);
  // for (int i  = 0; i < 52; i++)
     // print_card(&deck[i]);
   
   
   //run the program for 10000 hands
  srand ( time(NULL) ); 
  for (int i = 1; i < total_hands+1; i++)
      { 
      shuffle_deck(deck);
      deal_5_card_hand(deck, hand); 		//a hand is created in the array hand now
      num_of_pairs(hand, pairs);		//the pairs are in the array pairs
      which_hand(pairs, &no_pair, &one_pair, &two_pair, &three_of_a_kind, &four_of_a_kind, &full_house); 
      }  

   printf("\n\n\nNumber of no pairs is %d. The probability of getting no pairs is %lf", no_pair, (no_pair/total_hands));
   printf("\nNumber of one pairs is %d. The probability of getting one pairs is %lf", one_pair, (one_pair/total_hands));
   printf("\nNumber of two pairs is %d. The probability of getting two pairs is %lf", two_pair, (two_pair/total_hands));
   printf("\nNumber of three of a kinds is %d. The probability of getting three of a kinds is %lf", three_of_a_kind, (three_of_a_kind/total_hands));
   printf("\nNumber of four of a kinds is %d. The probability of getting four of a kinds is %lf", four_of_a_kind, (four_of_a_kind/total_hands));
   printf("\nNumber of full houses is %d. The probability of getting full houses is %lf", full_house, (full_house/total_hands));


   /*
   //make a hand
   deal_5_card_hand(deck, hand);
   printf("This is the hand\n");
   for (int i = 0; i < 5; i++)
      print_card(&hand[i]);

   //test num_of_pairs (hand, pairs)
   for (int i = 0; i <= 4; i++)
      print_card(&hand1[i]);
   num_of_pairs(hand1, pairs);
   printf("\nAnalysis ran...\n");
   printf("Num of pairs is: %d\n", pairs[0]);
   printf("Num of three of a kind is: %d\n", pairs[1]);
   printf("Num of four of a kind is: %d\n", pairs[2]);
   
   printf("%d", which_hand(pairs));
   */

   
   return 0;
   }

