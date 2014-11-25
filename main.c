#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "hex.h"

#define TRUE 1
#define FALSE 0

void init_field(Hexagon** field, int L, int A, unsigned s)
{
    int i,j,k = 0;
    
    #pragma omp parallel for private(i, j)
    for (k = 0; k < L*A; k++)
    {
        i = k/L;
        j = k % L;
        field[i][j].bug = TRUE;
        field[i][j].seed = ((i + 1) * s + j) % RAND_MAX;
        field[i][j].lastUpdated = 0;
        field[i][j].whoWantsMore = -1;
        field[i][j].wantValue = -1.0;
    }

}

void init_bugs(Hexagon* bugs, Hexagon** field, int j, int L, int A, unsigned* s)
{
    int x, y, i = 0;
    #pragma omp parellel for private(x, y)
    for (i = 0; i < j; i++) 
    {
        do
        {
            x = rand_r(s) % L; 
            y = rand_r(s) % A; 
        } while (field[x][y].bug);
        field[x][y].bug = TRUE;
        bugs[i] = field[x][y];
    }
}

void spawn(Hexagon** field, int L, int A, float pc, float pf, int nc, int nf)
{
    float val;
    int i, j, k;
    #pragma omp parallel for private(i, j, val)
    for (k = 0; k < L*A; k++)
    {
        i = k/L;
        j = k % L;
        
        if (field[i][j].bug)
            continue;

        val = (1.0*rand_r(&field[i][j].seed)) / RAND_MAX;
        if (val <= pc)
            field[i][j].heat = nc;
        val = (1.0*rand_r(&field[i][j].seed)) / RAND_MAX;
        if (val <= pf)
            field[i][j].cold = nf;
    }
}

int main(int argc, char* argv[])
{
    int L = 100, A = 100;
    int j = 10;
    unsigned int s = 42;
    float C = 2;
    float tmin = 0.0, tmax = 100.0;
    float pc = 0.1, pf = 0.1;
    int nc = 2, nf = 2;
    int T = 10;
    int P = 4;
    int iter;

    int i, x, y;
    
    Hexagon* bugs;
    Hexagon** field;


    srand(s);

    field = (Hexagon**) malloc(A*sizeof(Hexagon*));

    #pragma omp parallel for
    for (i = 0; i < A; i++)
        field[i] = (Hexagon*) malloc(L*sizeof(Hexagon));

    init_field(field, L, A, s);

    bugs = (Hexagon*) malloc(j*sizeof(Hexagon));
    init_bugs(bugs, field, j, L, A, &s);
    
    for (iter = 0; iter < T; i++)
    {
        spawn(field, L, A, pc, pf, nc, nf);
    }

    #pragma omp parallel for
    for (i = 0; i < A; i++)
        free(field[i]);
    free(field);
    free(bugs);

    return 0;

}
