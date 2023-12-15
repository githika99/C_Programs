#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "ss.h"
#include"numtheory.h"

void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    mpz_t mod1, mod2, tempq, tempp;
    mpz_inits(mod1, mod2, tempq, tempp, NULL);

    uint64_t pbits = (rand() % ((2*nbits)/5)) + (nbits/5);
    uint64_t qbits = nbits - (2*pbits);

    do {
    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);
    mpz_sub_ui(tempp, p, 1);
    mpz_sub_ui(tempq, q, 1);
    mpz_mod(mod1, tempq,p);
    mpz_mod(mod2, tempp ,q);
    } while(mpz_cmp_d(mod1, 0) == 0 || mpz_cmp_d(mod2, 0) == 0);        //while one of them does divide the other, remake.
    //check that p does not divide (q - 1) and that q does not divide (p - 1)
    mpz_mul(n, p, p);
    mpz_mul(n, n, q);       //n = p*p * q

    mpz_clears(mod1, mod2, tempq, tempp, NULL);
}

void new_pp(mpz_t pp, mpz_t pp_1, mpz_t pp_2, mpz_t qq_2, mpz_t n_copy) {
        mpz_mul(pp, pp_1, qq_2);
        mpz_sub(pp, pp_2, pp);
        mpz_mod(pp, pp, n_copy);
}

void update(mpz_t pp, mpz_t pp_1, mpz_t pp_2, mpz_t qq, mpz_t qq_1, mpz_t qq_2) {
        mpz_set(pp_2, pp_1);
        mpz_set(pp_1, pp);
        mpz_set(qq_2, qq_1);
        mpz_set(qq_1,qq);
}

void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    //d the inverse of n mod lcm(p-1, q-1)
    //find least common multiple of p-1 and q-1 and set it to d.
    mpz_t n_copy, pp, qq, pp_1, pp_2, qq_1, qq_2, temp, remainder, a, n, lcm, divisor, product, tempp, tempq;
    mpz_init_set_d(pp_2, 0);
    mpz_init_set_d(pp_1, 0);
    mpz_init_set_d(qq_2, 0);
    mpz_inits(pp, qq, qq_1, temp, remainder, a, n,lcm, divisor, product, tempp, tempq, NULL);

    //set n
    mpz_mul(n, p, p);
    mpz_mul(n, n, q);   //n = p^2 * q
    mpz_init_set(n_copy, n);

    //find lcm of p-1 and q-1
    mpz_sub_ui(tempp, p, 1);
    mpz_sub_ui(tempq, q, 1);
    gcd(divisor, tempp, tempq);
    mpz_mul(product, tempp, tempq);
    mpz_fdiv_q(lcm, product, divisor);

    //gmp_printf("lcm of %Zd and %Zd equals %Zd", tempp, tempq, lcm);
    //REMOVE FOR FINAL SUBMISSION
    mpz_set(a, lcm);

    bool inverse = false;
    int count = 0;

    while(mpz_cmp_d(a, 0) != 0) {                       //while a != 0
        //gmp_printf("\n\nn is %Zd\n", n);
        //gmp_printf("a is %Zd\n", a);
        mpz_fdiv_q(qq, n, a);             //g is floor div of lcm/n
        if (count == 0)
            mpz_set_d(pp, 0);
        else if (count == 1)
            mpz_set_d(pp, 1);
        else {
            new_pp(pp, pp_1, pp_2, qq_2, n_copy);
            //gmp_printf("pp is now %Zd\n", pp);
        }

        mpz_mul(remainder, qq, a);
        mpz_fdiv_r(remainder, n, a);
        //gmp_printf("remainder is %Zd\n", remainder);

        if(mpz_cmp_d(a, 1) == 0 && mpz_cmp_d(remainder, 0) == 0) {                //if a == 1 and remainder == 0 break
                inverse = true;
                break;
        }
        mpz_set(temp, a);
        mpz_mul(a, qq, a);
        mpz_fdiv_r(a, n, a);    //a = (n/qq*q) remainder
        mpz_set(n, temp);       //n = a

        //next round of variables
        update(pp, pp_1, pp_2, qq, qq_1, qq_2);
        count++;
    }
    if (inverse) {
        new_pp(pp, pp_1, pp_2, qq_2, n_copy);
        //gmp_printf("pp is now %Zd\n", pp);
        update(pp, pp_1, pp_2, qq, qq_1, qq_2);

        new_pp(pp, pp_1, pp_2, qq_2, n_copy);
        //gmp_printf("pp is now %Zd\n", pp);
        update(pp, pp_1, pp_2, qq, qq_1, qq_2);
        mpz_set(d, pp);
   }
   else
           mpz_set_d(d, 0);

   mpz_mul(pq, p, q);
   //gmp_printf("result of inverse of %Zd mod %Zd is %Zd\n", a, n, d);
   mpz_clears(n_copy, pp, qq, pp_1, pp_2, qq_1, qq_2, temp, remainder, a, n, lcm, divisor, product, tempp, tempq, NULL);
}



void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile){
    //assume file is open
    // Convert n to a hexstring
    char *hex = mpz_get_str(NULL, 16, n);
    fprintf(pbfile, "%s\n", hex);
    fprintf(pbfile, "%s\n", username);
    free(hex);
}


void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    //assume file is open
    // Convert n to a hexstring
    char *hex_pq = mpz_get_str(NULL, 16, pq);
    char *hex_d = mpz_get_str(NULL, 16, d);
    fprintf(pvfile, "%s\n", hex_pq);
    fprintf(pvfile, "%s\n", hex_d);
    free(hex_pq);
    free(hex_d);
}

void ss_read_pub(mpz_t n, char username[], FILE *pbfile){
        char buffer[1024];
        fscanf(pbfile, "%s\n", buffer);
        mpz_set_str(n, buffer, 16);             //16 makes hexfile into base 10 in n
        fscanf(pbfile, "%s\n", username);
}


void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
        char buffer_pq[1024];
        char buffer_d[1024];
        fscanf(pvfile, "%s\n", buffer_pq);
        mpz_set_str(pq, buffer_pq, 16);
        fscanf(pvfile, "%s\n", buffer_d);
        mpz_set_str(d, buffer_d, 16);

}


void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n);
}

void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq);
}

void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    //char buffer;
    uint64_t  k;
    mpz_t m, c, temp;
    mpz_inits(m, c, temp, NULL);
    mpz_sqrt(temp, n);     //temp = sqrt(n)
    mpz_sub_ui(temp, temp, 1);   //temp = temp - 1
    k = mpz_get_ui(temp);
    k = (log(k)/log(2))/8;
    //printf("\nk is %lu\n", k);

    //while there are still unprocessed bits in the file
        //reads k-1 chars and adds to ptr.
        while (!feof(infile)) {
            uint8_t * ptr = (uint8_t * )malloc(k * sizeof(uint8_t));  //dynamically allocate memory
            ptr[0] = 0xFF;
            int j = fread(ptr, sizeof(uint8_t), k-1, infile); // read at most k-1 bytes from infile
            if (j <= 0) {
                break;
            }
            ptr[j] = '\0'; // null-terminate the array
            mpz_import(m, j, 1, sizeof(uint8_t), 1, 0, ptr); // convert the read bytes to an mpz_t m
            ss_encrypt(c, m, n);    //c is result
            gmp_fprintf(outfile, "%Zx\n", c); // print m to outfile as a hex string followed by a newline
            free(ptr);
        }
    
    mpz_clears(m, c, temp, NULL);
}

//void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq) {   }

/*
int main() {
    mpz_t d, p, q, n;
    mpz_inits(p, q, n , NULL);
    uint64_t nbits = 64;
    uint64_t iters = 10;

    //FILE *infile = fopen("input.txt", "r");
    //FILE *outfile = fopen("output.txt", "w");
    ss_make_pub(p, q, n, nbits, iters);
 
    gmp_printf("\np is %Zd. q is %Zd. n is %Zd.\n", p, q, n);
    //fclose(infile);
    //fclose(outfile);

    mpz_clears(p, q, n, NULL);

    return 0;
}
*/
    
