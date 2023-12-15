#include <stdio.h>
#include <unistd.h>
#include <math.h>
#define OPTIONS "aebmrvnsh"
#include "mathlib.h"

//Makefile just needs to run this.
//add absolute values for all differences

int main(int argc, char **argv) {
   int opt = 0;
     int s = 0;
     int n = 0;
     int v = 0;
     int r = 0;
     int m = 0;
     int b = 0;
     int e_var = 0;
     int a = 0;
      while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

      switch(opt) {
      case 'a': a = 1;
               break;
      case 'e': e_var = 1;
                break;
      case 'b': b = 1;
                break;
      case 'm': m = 1;
                break;
      case 'r': r = 1;
                break;
      case 'v': v = 1;
                break;
      case 'n': n = 1;
                break;
      case 's':s = 1;
               break;
      case 'h': printf("SYNOPSIS\n\tA test harness for the small numerical library.\n\nUSAGE\n\t./mathlib-test-arm64 [-aebmrvnsh]\n\nOPTIONS\n  -a   Runs all tests.\n  -e   Runs e test.\n  -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n  -r   Runs Euler pi test.\n  -v   Runs Viete pi test.\n  -n   Runs Newton square root tests.\n  -s   Print verbose statistics.\n  -h   Display program synopsis and usage."); break;
      default: printf("SYNOPSIS\n\tA test harness for the small numerical library.\n\nUSAGE\n\t./mathlib-test-arm64 [-aebmrvnsh]\n\nOPTIONS\n  -a   Runs all tests.\n  -e   Runs e test.\n  -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n  -r   Runs Euler pi test.\n  -v   Runs Viete pi test.\n  -n   Runs Newton square root tests.\n  -s   Print verbose statistics.\n  -h   Display program synopsis and usage.");
   }
   }
     //outside switch and outside for loop


      if (a && !s){
                printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", e(), M_E, absolute(M_E - e()));
                printf("pi_euler() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
                printf("pi_bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_bbp(), M_PI, absolute(M_PI - pi_bbp()));
                printf("pi_madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()));
                printf("pi_viete() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()));
                for (double i = 0; i <= 10; i += .1){
                  printf("sqrt_newton(%f) = %.15f, sqrt(%f) = %.15f, diff = %.15f\n", i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));}}
      if (a && s){
                printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", e(), M_E, absolute(M_E - e()));
                printf("e_terms() terms = %d\n", e_terms());
                printf("pi_euler() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
                printf("pi_euler_terms() terms = %d\n", pi_euler_terms());
                printf("pi_bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_bbp(), M_PI, absolute(M_PI - pi_bbp()));
                printf("pi_bbp_terms() terms = %d\n", pi_bbp_terms());
                printf("pi_madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()));
                printf("pi_madhava_terms() terms = %d\n", pi_madhava_terms());
                printf("pi_viete() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()));
                printf("pi_viete_factors() terms = %d\n", pi_viete_factors());
                for (double i = 0; i <= 10; i += .1){
                  printf("sqrt_newton(%f) = %.15f, sqrt(%f) = %.15f, diff = %.15f\n", i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));

                  printf("sqrt_newton_iters() terms = %d\n", sqrt_newton_iters());}}
     if (e_var && !s)
             printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", e(), M_E, absolute(M_E - e()));
     if (e_var && s){
        printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", e(), M_E, absolute(M_E - e()));
        printf("e_terms() terms = %d\n", e_terms());}

 
    if (b && !s)
        printf("pi_bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_bbp(), M_PI, absolute(M_PI - pi_bbp()));
      if (b && s){
        printf("pi_bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_bbp(), M_PI, absolute(M_PI - pi_bbp()));
        printf("pi_bbp_terms() terms = %d\n", pi_bbp_terms());}

      if (m && !s)
         printf("pi_madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()));
      if (m && s){
        printf("pi_madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()));
        printf("pi_madhava_terms() terms = %d\n", pi_madhava_terms());}

      if (r && !s)
        printf("pi_euler() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
      if (r && s){
        printf("pi_euler() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
        printf("pi_euler__terms() terms = %d\n", pi_euler_terms());}

      if (v && !s)
        printf("pi_viete() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()));
      if (v && s){
        printf("pi_viete() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()));
        printf("pi_viete_factors() terms = %d\n", pi_viete_factors());}

     if (n && !s){
             for (double i = 0; i <= 10; i += .1){
                  printf("sqrt_newton(%f) = %.15f, sqrt(%f) = %.15f, diff = %.15f\n", i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));}}
     if (n && s){
             for (double i = 0; i <= 10; i += .1){
                  printf("sqrt_newton(%f) = %.15f, sqrt(%f) = %.15f, diff = %.15f\n", i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)) );

                  printf("sqrt_newton_iters() terms = %d\n", sqrt_newton_iters());}
             }

      return 0;
}



