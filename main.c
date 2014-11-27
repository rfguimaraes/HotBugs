#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "hex.h"

#define TRUE 1
#define FALSE 0

void init_field(Hexagon** field, int L, int A, unsigned s, int* sources)
{
    int i,j,k = 0;
    
    #pragma omp parallel for private(i, j) shared(field, s, k) schedule(dynamic)
    for (k = 0; k < L*A; k++)
    {
        i = k/L;
        j = k % L;
        printf("%d %d %d\n", i ,j, k);
        field[i][j].bug = FALSE;
        field[i][j].seed = ((i + 1) * s + j) % RAND_MAX;
        field[i][j].lastUpdated = 0;
        field[i][j].whoWantsMore = -1;
        field[i][j].wantValue = -1.0;
    }
}

void init_bugs(int* bugs, Hexagon** field, int j, int L, int A, unsigned* s)
{
    int x, y, i = 0;
    #pragma omp parellel for private(x, y) shared(field) schedule(dynamic)
    for (i = 0; i < j; i++) 
    {
        do
        {
            x = rand_r(s) % L; 
            y = rand_r(s) % A; 
        } while (field[x][y].bug == TRUE);
        field[x][y].bug = TRUE;
        bugs[i] = x*L + y;
    }
}

void spawn(Hexagon** field, int L, int A, float pc, float pf, int nc, int nf, int* sources, int bugs)
{
    float val;
    int i, j, k;
    int offset = bugs;
    #pragma omp parallel for private(i, j, val) schedule(dynamic)
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
        if (field[i][j].heat || field[i][j].cold)
            sources[offset++] = k; 
    }
    #pragma omp single
    sources[offset] = -1;
    printf("FIRE INIT");
}

void calc_bug_temps(Hexagon** field, int L, int A, int sources, int j, float C)
{
    int iter;
    int reader = 0;

    for (iter = 0; iter < j; i++)
    {
        while (sources[reader] != -1)
        {
            CALCULATIONS
            reader++;
        }
    }
}

int main(int argc, char* argv[])
{
    int L = 10, A = 10;
    int j = 10;
    unsigned int s = 42;
    float C = 2.0;
    float tmin = 0.0, tmax = 100.0;
    float pc = 0.1, pf = 0.1;
    int nc = 2, nf = 2;
    int T = 1;
    int P = 4;
    int iter;

    int i, x, y;
    
    int* sources;
    Hexagon** field;


    srand(s);

    field = (Hexagon**) malloc(A*sizeof(Hexagon*));
    sources = (int*) malloc((L*A + 1)*sizeof(int));

    #pragma omp parallel for
    for (i = 0; i < A; i++)
        field[i] = (Hexagon*) malloc(L*sizeof(Hexagon));

    init_field(field, L, A, s, sources);
    printf("ASDASD");

    init_bugs(sources, field, j, L, A, &s);
    
    for (iter = 0; iter < T; iter++)
    {
        spawn(field, L, A, pc, pf, nc, nf, sources, j);
    }

    #pragma omp parallel for
    for (i = 0; i < A; i++)
        free(field[i]);
    free(field);
    free(sources);

    return 0;

}
