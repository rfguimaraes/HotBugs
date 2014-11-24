#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "hex.h"

void init_field(Hexagon** field, int L, int A, int s)
{
    int i,j,k = 0;
    
    #pragma omp parallel for
    for (k = 0; k < L*A; k++)
    {
        i = k/L;
        j = k % L;
        field[i][j].entity = NORMAL;
        field[i][j].seed = ((i + 1) * s + j) % RAND_MAX;
        field[i][j].lastUpdated = 0;
        field[i][j].whoWantsMore = -1;
        field[i][j].wantValue = -1.0;
    }

}

int main(int argc, char* argv[])
{
    int L = 10000, A = 10000;
    int j = 10;
    int s = 42;
    float C = 2;
    float tmin = 0.0, tmax = 100.0;
    float pc = 0.1, pf = 0.1;
    int nc = 2, nf = 2;
    int T = 10;
    int P = 4;

    int i;
     
    Hexagon** field;

    field = (Hexagon**) malloc(A*sizeof(Hexagon*));
    #pragma omp parallel for
    for (i = 0; i < A; i++)
        field[i] = (Hexagon*) malloc(L*sizeof(Hexagon));

    init_field(field, L, A, s);

    #pragma omp parallel for
    for (i = 0; i < A; i++)
        free(field[i]);
    free(field);

    return 0;

}
