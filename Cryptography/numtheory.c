#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "numtheory.h"

void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n){
    mpz_t v, p, e, mod; mpz_init_set_d(v, 1);

    mpz_init_set(p, a);

    mpz_init_set(e, d);

    mpz_init_set(mod, a);

    while(mpz_cmp_d(e, 0) > 0) {            //while d > 0
        if (mpz_mod_ui(mod, e, 2) == 1) {   //if d is odd
            mpz_mul(v, v, p);      //v = v * p
            mpz_mod(v, v, n);       //v = v mod n
        }
        mpz_mul(p, p, p);           //p = p * p
        mpz_mod(p, p, n);           //p = p mod n
        mpz_fdiv_q_ui(e, e, 2);        //d is d/2
    }   
    mpz_set(o, v);
    mpz_clears(v, p, e, mod, NULL);
}

void gcd(mpz_t g, const mpz_t a, const mpz_t b) {

    mpz_t v1, v2, temp; mpz_init_set(v1, a);

    mpz_init_set(v2, b);

    mpz_init(temp);

    while(mpz_cmp_d(v2, 0) != 0) {          //v2 != 0
        mpz_set(temp, v2);                       //for set, (pointer, const)
        mpz_mod(v2, v1, v2);
        mpz_set(v1, temp);
    }
    mpz_set(g, v1);
    mpz_clears(temp, v1, v2, NULL);
}


void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {
    mpz_t r, rn, t, tn, q, temp; mpz_init_set(r, n);

    mpz_init_set(rn, a);

    mpz_init_set_d(t, 0);

    mpz_init_set_d(tn, 1);

    mpz_inits(q, temp, NULL);

    while(mpz_cmp_d(rn, 0) != 0) {      //rn 1= 0
        mpz_fdiv_q(q, r, rn);

        mpz_set(temp, r);
        mpz_set(r, rn);             //r = rn
        mpz_mul(rn, q, rn);          //rn = q * rn
        mpz_sub(rn, temp, rn);         //rn = r - rn

        mpz_set(temp, t);
        mpz_set(t, tn);             //t = rn
        mpz_mul(tn, q, tn);          //tn = q * tn
        mpz_sub(tn, temp, tn);         //tn = t - tn
    }

    if (mpz_cmp_d(rn, 1) > 0) {
        mpz_set_d(o, 0);            //if there is no modulo inverse
        return;
    }
    if (mpz_cmp_d(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    mpz_set(o, t);
    mpz_clears(r, rn, t, tn, q, temp, NULL);
}


bool is_prime(const mpz_t n, uint64_t iters) {

    mpz_t num, mod, s, base, two, y, temps, tempn, j, d;
    mpz_init_set(num, n);
    mpz_inits(mod, base, y, temps, tempn, j, NULL);
    mpz_init_set_d(s, 0);
    mpz_init_set_d(two, 2);
    mpz_init_set(d, n); mpz_sub_ui(d, d, 1);       //d = n -1

    mpz_mod_ui(mod, d, 2);
    while (mpz_cmp_d(mod, 0)  == 0) {     //2^s * d = n - 1
        mpz_fdiv_q_ui(d, d, 2);     //d = d/2
        mpz_add_ui(s,s,1);             //s++;
        mpz_mod_ui(mod, d, 2);
    }
    for (uint64_t i = 0; i < iters; i++) {
        mpz_sub_ui(tempn, num, 2);

        //CALL randstate_init(uint64_t seed) rather than doing this
        gmp_randstate_t state1;
        gmp_randinit_mt(state1);
        gmp_randseed_ui(state1, rand());

        mpz_urandomm(base, state1, tempn);
        mpz_add_ui(base, base, 2);          //base is random 'a' from {2, n-2}

        pow_mod(y, base, d, num);
        mpz_sub_ui(tempn, num, 1);
        if (mpz_cmp_d(y, 1) != 0 && mpz_cmp(y, tempn) != 0) {      //if y != 1 and y != (n -1)
            mpz_set_d(j, 1);
            mpz_sub_ui(temps, s, 1);
            //j <= (s - 1) && y != (n - 1)
            while (mpz_cmp(j, temps) <= 0 && mpz_cmp(y, tempn) != 0) {
                pow_mod(y, y, two, num);
                if (mpz_cmp_d(y, 1) == 0)   //y == 1
                    return false;
                mpz_add_ui(j, j, 1);         //j = j + 1
        }
            mpz_sub_ui(num, num, 1);                                   //n = n - 1
            if (mpz_cmp(y, num) != 0)                                      //y != (n -1)      
                return false;
        }

        //CALL randstate_clear(void) rather than doing this
        gmp_randclear(state1);
    }
    mpz_clears(num, mod, s, base, two, y, temps, tempn, j, d, NULL);
        return true;
 }



void make_prime(mpz_t p, uint64_t bits, uint64_t iters){
    //CALL randstate_init(uint64_t seed) rather than doing this
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, rand());

    do {
        mpz_urandomb(p, state, bits);
        mpz_setbit(p, bits - 1);
        mpz_setbit(p, 0);
    } while(!is_prime(p, iters));

   //CALL randstate_clear(void) rather than doing this
   gmp_randclear(state);

}


/*
int main() {
    srand(time(NULL));      //set seed one time in main program

    mpz_t a; mpz_init(a);

    mpz_t b; mpz_init(b);

    mpz_t c; mpz_init(c);

    mpz_t d; mpz_init_set_d(d, 7);

    mpz_set_ui(a, 16); mpz_set_ui(b, 2);

    gcd(c, b, a);

    gmp_printf("gcd: %Zd\n", c);

    mod_inverse(c, b, a);

    gmp_printf("mod inverse: %Zd\n", c);

    pow_mod(c, a, b, d);

    gmp_printf("pow mod: %Zd\n", c);

    if (is_prime(d, 10))
        printf("is prime \n");
    else
        printf("not prime\n");

    make_prime(a, 32, 10);
    gmp_printf("Prime number with %u bits:  %Zd\n", 32, a);

    mpz_clears(a,b,c,d,NULL);
    return 0;
}
*/
