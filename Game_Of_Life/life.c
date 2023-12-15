#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "universe.h"
#define OPTIONS "tsn:i:o:"
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#define DELAY 50000


int main(int argc, char **argv){

        int opt = 0;
        FILE *infile = fopen("stdin", "r");
        FILE *outfile = fopen("stdout", "w");
        uint32_t generations = 100;                       //MAKE 100 BEFORE SUBMITTING!!!
        bool ncurses = false;
        bool toroidal = false;

        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
                case't': toroidal = true; break;
                case's': ncurses = false; break;
                case'n': generations = (uint32_t)strtoul(optarg, NULL, 10); 
                        if (generations < 1) {
                                printf("Generations must be greater than 0");
                                return 0;
                        }
                        break;
                case'i': 
                        infile = fopen(optarg, "r");
                        if(infile == NULL) {
                                printf("Input file: does not exist");
                                return 0;
                        }
                        break;
                case'o': outfile = fopen(optarg, "w"); break;
        }
        }

        uint32_t rows;
        uint32_t cols;

        fscanf(infile, "%d %d" , &rows, &cols);

        Universe *UniA = uv_create(rows, cols, toroidal);
        Universe *UniB = uv_create(rows, cols, toroidal);
        if (!uv_populate(UniA, infile)){
                uv_delete(UniA);
                printf("Malformed input.");             //if returns False, stop execution and give error message.
                return 0;}
        for (uint32_t g = 0; g < generations; g++) {

                

                uint32_t n = 0;
                for (uint32_t r = 0; r < rows; r++) {
                                for (uint32_t c = 0; c < cols; c++) {
                                        n = uv_census(UniA, r, c);
                                        if (uv_get_cell(UniA, r, c) && (n == 2 || n == 3)) {
                                                uv_live_cell(UniB, r, c); }

                                        else if ((!uv_get_cell(UniA, r, c)) && n == 3) {
                                                uv_live_cell(UniB, r, c);}

                                        else {
                                                uv_dead_cell(UniB, r, c);}
                                }
                }
                //swap should be working :)
                Universe *temp = UniA;
		        UniA = UniB;
		        UniB = temp;

        }
        uv_print(UniA, outfile);
        uv_delete(UniA);
        uv_delete(UniB);
        return 0;
}
