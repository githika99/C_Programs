#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <gmp.h>
#include <sys/stat.h>
#include "randstate.h"
#include "ss.h"
#define OPTIONS "b:i:n:d:vh"

int main (int argc, char **argv) {
    int opt = 0;
    uint32_t bits =  256;
    uint32_t iters =  50;
    uint32_t seed = time(NULL);
    FILE *pub = fopen("ss.pub", "w");
    FILE *priv = fopen("ss.priv", "w");
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
                case 'b': bits = (uint32_t)strtoul(optarg, NULL, 10); break;
                case 'i': iters = (uint32_t)strtoul(optarg, NULL, 10); break;
                case'n':
                        pub = fopen(optarg, "r");
                        if(pub == NULL) {
                                printf("Public key file does not exist");
                                return 0;
                        }
                        break;
                case'd':
                        priv = fopen(optarg, "r");
                        if(priv == NULL) {
                                printf("Private key file does not exist");
                                return 0;
                        }
                        break;

                case's': seed = (uint32_t)strtoul(optarg, NULL, 10); break;
                case'v': verbose = true; break;
                case 'h':
                        printf("SYNOPSIS\n\tGenerates an SS public/private key pair.\n\nUSAGE\n\t./encrypt [OPTIONS]\n\nOPTIONS\n\t-h              Display program help and usage.\n\t-v              Display verbose program output.\n\t-b bits         Minimum bits needed for public key n (default: 256).\n\t-i iterations   Miller-Rabin iterations for testing primes (default: 50).\n\t-n pbfile       Public key file (default: ss.pub).\n\t-d pvfile       Private key file (default: ss.priv).\n\t-s seed         Random seed for testing.");
                        return 0; break;
        }
        }

    if(pub == NULL) {
            printf("Public key file does not exist");
            return 0;
     }

     if(priv == NULL) {
            printf("Private key file does not exist");
             return 0;
     }

     int file_descriptor = fileno(priv);
     int result = fchmod(file_descriptor, S_IRUSR | S_IWUSR);

    if (result == -1) {
        printf("fchmod error");
        return 0;
    }


    randstate_init(seed);

    mpz_t p, q, n, pq, d;
    mpz_inits(p, q, n, pq, d, NULL);
    ss_make_pub(p, q, n, bits, iters);
    //gmp_printf("\np is %Zd. q is %Zd. n is %Zd.\n", p, q, n);
    ss_make_priv(d, pq, p, q);
    //gmp_printf("\nd is %Zd. pq is %Zd.\n", d, pq);

    char *username = getenv("USER");
    if (username == NULL) {
        printf("Unable to get username\n");
        return 0;
    }

    ss_write_pub(n, username, pub);
    
    ss_write_priv(pq, d, priv);

    if (verbose) {
        printf("%s\n", username);
        gmp_printf("%Zd\n", p);
        gmp_printf("%Zd\n", q);
        gmp_printf("%Zd\n", n);
        gmp_printf("%Zd\n", d);
        gmp_printf("%Zd\n", pq);
    }
    mpz_clears(p, q, n, pq, d, NULL);
    fclose(pub);
    fclose(priv);
    randstate_clear();
    return 0;
}


