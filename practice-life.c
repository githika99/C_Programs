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

//do input/output from files

//void UniSwap(Universe *A, Universe *B);

int main(int argc, char **argv){

        int opt = 0;
        char *input_name = "inputfile.txt";             //change to stdin for final submission
        char *output_name = "output.txt";
        uint32_t generations = 2;                       //MAKE 100 BEFORE SUBMITTING!!!
        bool ncurses = false;
        bool toroidal = false;

        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
                case't': toroidal = true; break;
                case's': ncurses = false; break;
                case'n': generations = (uint32_t)strtoul(optarg, NULL, 10); break;
                case'i':  break;
                case'o':  break;
        }
        }

        FILE *infile = fopen(input_name, "r");
        FILE *outfile = fopen(output_name, "w+");
        FILE *f = fopen("f1.txt", "w+");
        FILE *after = fopen("after.txt", "w+");
 FILE *before = fopen("before.txt", "w+");

        uint32_t rows;
        uint32_t cols;

        fscanf(infile, "%d %d" , &rows, &cols);

        Universe *UniA = uv_create(rows, cols, toroidal);
        Universe *UniB = uv_create(rows, cols, toroidal);
        if (!uv_populate(UniA, infile)){
                uv_delete(UniA);
                printf("Malformed input.");             //if returns False, stop execution and give error message.
                return 0;}
        uv_populate(UniB, infile);
        uv_print(UniA, f);

        for (uint32_t g = 0; g < generations; g++) {

                //print for each generation
                if (ncurses){
                        initscr();
                        curs_set(FALSE);
                        clear();
                        for (uint32_t r = 0; r < rows; r++) {
                                for (uint32_t c = 0; c < cols; c++) {
                                        //clear();
                                        if (uv_get_cell(UniA, r, c))
                                                mvprintw(r, c, "o");
                                                //usleep(DELAY);
                                                //refresh();
                                refresh();
                                usleep(DELAY);

                                }
                        }
                        //refresh();
                       // usleep(DELAY);
                        endwin();
                }
                                 
                //perform one generation
                uint32_t n = 0;
                printf("\n\ngeneration # %u\n\n", g);
                for (uint32_t r = 0; r < rows; r++) {
                                for (uint32_t c = 0; c < cols; c++) {
                                        n = uv_census(UniA, r, c);
                                        printf("(%u, %u) has %u neighbors\n", r, c, n);
                                        if (uv_get_cell(UniA, r, c) && (n == 2 || n == 3))
                                                printf("(%u, %u) stays alive\n", r, c);
                                        else if (!uv_get_cell(UniA, r, c) && n == 3) {
                                                printf("(%u, %u) becomes alive\n", r, c);
                                                uv_live_cell(UniB, r, c);}
                                        else {
                                                //printf("(%u, %u) becomes dead\n", r, c);
                                                uv_dead_cell(UniB, r, c);}
                                }
                }

                //swap uniA and uniB
                uv_print(UniA, before);         //
                //UniSwap(UniA, UniB);
                uv_print(UniA, after);          //should be dif from before

        }
        uv_print(UniA, outfile);


        uv_delete(UniA);
        uv_delete(UniB);
        return 0;
}
/*
void UniSwap(Universe *A, Universe *B) {
        Universe *t = A;
        A = B;
        B = t;
}
*/
