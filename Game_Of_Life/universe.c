#include "universe.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct Universe {
        uint32_t rows;
        uint32_t cols;
        bool **grid;
        bool toroidal;
};

Universe* uv_create(uint32_t rows, uint32_t cols, bool toroidal)        //returns a pointer of type Universe
{
       Universe* myUni = (Universe*)calloc(1, sizeof(Universe));
       bool** matrix = (bool **) calloc (rows, sizeof(bool *));      //allocates memory for the rows
       for (uint32_t r = 0; r < rows; r++)
       {
               matrix[r] = (bool *) calloc (cols, sizeof(bool));         //allocates col memory for each row
               if (matrix[r] == NULL)
                       printf("memory could not be allocated for row %u", r);
       }

       myUni -> grid = matrix;
       //set all variables to false
        for (uint32_t r = 0; r < rows; r++)
        {
                for(uint32_t c = 0; c < cols; c++)
                        myUni-> grid[r][c] = false;
        }
        myUni -> rows = rows;
        myUni -> cols = cols;
        myUni -> toroidal = toroidal;

        return myUni;
}

void uv_delete(Universe *u)
{
        //delete universe. free all variables
        //free inner most thing first, then propogate outside
        if (u == NULL)
                return;

        bool** matrix = u-> grid;

        uint32_t rows = uv_rows(u);
        if (matrix != NULL)
        {

        for(uint32_t r = 0; r < rows; r++)
                free(u -> grid[r]);

        free(matrix);
        }

        free(u);                //frees universe
}

uint32_t uv_rows(Universe *u)
{
return u -> rows;
}

uint32_t uv_cols(Universe *u)
{
return u -> cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c)
{
        uint32_t rows = uv_rows(u);
        uint32_t cols = uv_cols(u);

        if (r < rows && c < cols)
                u-> grid[r][c] = true;
        //sets cell to alive if it is in bounds
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c)
{
        uint32_t rows = uv_rows(u);
        uint32_t cols = uv_cols(u);

        if (r < rows && c < cols)
                u-> grid[r][c] = false;
        //sets cell to dead if it is in bounds
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
        uint32_t rows = uv_rows(u);
        uint32_t cols = uv_cols(u);

        if (r < rows && c < cols)
                return (u->grid[r][c]); //either true or false

        return false;

}

bool uv_populate(Universe *u, FILE *infile) {
        uint32_t inp1, inp2;
        int count = 0;
        while ( fscanf(infile, "%d %d" , &inp1, &inp2) != EOF ) {
                        if(inp1 < u->rows && inp2 < u->cols)
                                u->grid[inp1][inp2] = true;
                        else
                                return false;                           //cell was outside bounds
                count++;

        }
        fclose(infile);         //just for fun, file closes regardless
        return true;
}


bool isNeighbor(Universe *u, int r1, int c1, bool toroidal) {
        int rows = uv_rows(u);
        int cols = uv_cols(u);

        if (! toroidal){
                if (r1 < rows && c1 < cols && r1 >= 0 && c1 >= 0)       //(r1, c1) is in bounds
                        return(u->grid[r1][c1]);
                return false;
        }

        //if toroidal
        if (r1 == rows){
                //printf("%d was changed to %d", r1, 0);
                r1 = 0;}
        if (c1 == cols){
                //printf("%d was changed to %d", c1, 0);
                c1 = 0;}
        if (r1 < 0){
                //printf("%d was changed to %d", r1, 0);
                r1 = rows - 1;}
        if (c1 < 0){
                //printf("%d was changed to %d", r1, 0);
                c1 = cols - 1;}
        return (u->grid[r1][c1]);
}

uint32_t HowManyNeighbor(Universe *u, int r, int c, bool toroidal)  //returns True if (r1,c1) is a live neighbor of (r,c)  
{               //returns False if it is a dead neighbor, or if it is not a neighbor
        uint32_t aliveNeighbors = 0;
        int r1, c1;
        for(r1 = r - 1 ; r1 <= (r + 1); r1++){
                for(c1 = c - 1 ; c1 <= (c + 1); c1++){
                        if (!(r1 == r && c1 == c)){
                                if (isNeighbor(u, r1, c1, toroidal))
                                        aliveNeighbors++;
                        }
                }
        }
        return aliveNeighbors;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c)
{
        //returns number of alive neighbors
        bool toroidal = u-> toroidal;
        return HowManyNeighbor(u, r, c, toroidal);
}

void uv_print(Universe *u, FILE *outfile)
{
        uint32_t rows = uv_rows(u);
        uint32_t cols = uv_cols(u);


        for (uint32_t r = 0; r < rows; r++)
        {
                for (uint32_t c = 0; c < cols; c++)
                {
                        if (uv_get_cell(u, r, c))
                                fputs("o", outfile);
                        else
                                fputs(".", outfile);
                }
                fputs("\n", outfile);
        }

        fclose(outfile);
}

