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
    FILE *pub = fopen("ss.pub", "r");
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
                        pub = fopen(optarg, "r"); 
                        if(pub == NULL) {
                                printf("Public key file does not exist");
                                return 0;
                        } 
                        break;
                case'v': verbose = true; break;
                case 'h': 
                        printf("SYNOPSIS\n\tEncrypts data using SS encryption.\n\tEncrypted data is decrypted by the decrypt program.\n\nUSAGE\n\t./encrypt [OPTIONS]\n\nOPTIONS\n\t-h              Display program help and usage.\n\t-v              Display verbose program output.\n\t-i infile       Input file of data to decrypt (default: stdin).\n\t-o outfile      Output file for decrypted data (default: stdout).\n\t-n pbfile       Public key file (default: ss.pub)."); 
                        return 0; break;
        }
        }
    if(pub == NULL) {
                printf("Pubic key file does not exist");
                return;
        }

        if(infile == NULL) {
                printf("Input file does not exist");
                return;
        }


    mpz_t n;
    mpz_init(n);
    char username[1024];
    ss_read_pub(n, username, pub);
    if (verbose) {
            printf("%s\n", username);
            gmp_printf("%Zd\n", n);
    }
    ss_encrypt_file(infile, outfile, n);
    mpz_clear(n);
    fclose(pub);
    fclose(infile);
    fclose(outfile);
    return (0);
}
