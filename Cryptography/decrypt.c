#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "ss.h"
#define OPTIONS "i:o:n:vh"

int main (int argc, char **argv) {
    int opt = 0;
    FILE *infile = fopen("stdin", "r");;
    FILE *outfile = fopen("stdout", "w");
    FILE *priv = fopen("ss.priv", "r");
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
                case'i': 
                        infile = fopen(optarg, "r");
                        if(infile == NULL) {
                                printf("Input file does not exist");
                                return 0;
                        }
                        break;
                case'o': outfile = fopen(optarg, "w"); break;
                case'n': 
                        priv = fopen(optarg, "r"); 
                        if(priv == NULL) {
                                printf("Private key file does not exist");
                                return 0;
                        } 
                        break;
                case'v': verbose = true; break;
                case 'h': 
                        printf("SYNOPSIS\n\tDecrypts data using SS decryption.\n\tEncrypted data is encrypted by the encrypt program.\n\nUSAGE\n\t./decrypt [OPTIONS]\n\nOPTIONS\n\t-h              Display program help and usage.\n\t-v              Display verbose program output.\n\t-i infile       Input file of data to decrypt (default: stdin).\n\t-o outfile      Output file for decrypted data (default: stdout).\n\t-n pvfile       Private key file (default: ss.priv)."); 
                        return 0; break;
        }
        }
    if(priv == NULL) {
            printf("Private Key file does not exist");
            return;
        }

    mpz_t pq, d;
    mpz_inits(pq, d, NULL);
    ss_read_priv(pq, d, priv);

    if (verbose) {
            gmp_printf("%Zd\n", pq);
            gmp_printf("%Zd\n", d);
        }

    ss_decrypt_file(infile, outfile, d, pq);
    
    mpz_clears(pq, d, NULL);
    fclose(priv);
    fclose(outfile);
    fclose(infile);

    return 0;
}
