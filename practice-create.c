#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct Universe {
        uint32_t rows;
        uint32_t cols;
        bool **grid;
        bool toroidal;
};

uint32_t uv_cols(Universe *u)
{
return u -> cols;
}

uint32_t uv_rows(Universe *u)
{
return u -> rows;
}

void uv_delete(Universe *u)
{
        //delete universe. free all variables
        //free inner most thing first, then propogate outside
        uint32_t cols = uv_cols(u);
        uint32_t rows = uv_rows(u);
        for(uint32_t c = 0; c < cols; c++)           //frees columns
        {
                free(u -> grid[c]);
        }

        for(uint32_t r = 0; r < rows; r++)           //frees rows
        {
                free(u -> grid[r]);
        }

        //free(u -> grid);        //frees grid
        free(u);                //frees universe
}


Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal)
{
       Universe *myUni = (Universe*)calloc(1, sizeof(Universe));
       bool **matrix = (bool **) calloc (rows, sizeof(bool *));      //allocates memory for the rows
       for (uint32_t r = 0; r < rows; r++)
               matrix[r] = (bool *) calloc (cols, sizeof(bool));         //allocates col memory for each row

       myUni -> grid = matrix;
       //set all variables to false
        for (uint32_t r = 0; r < rows; r++)
        {
                for(uint32_t c = 0; c < cols; c++)
                        myUni-> grid[r][c] = false;
        }

        /*
       if (!myUni -> rows)
       {
                free(myUni);
                myUni = NULL;
       }
       */
        return myUni;
}

int main ()
{
        Universe Uni = *uv_create(5, 5, false);
        uv_delete(&Uni);
        return 0;
}

