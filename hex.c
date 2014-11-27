#include "hex.h"

/*# convert cube to even-r offset
q = x + (z + (z&1)) / 2
r = z*/

void cube_to_even_r(int* p, int* i, int *j)
{
    #pragma omp parallel sections shared(c0, c1, c2)
    {
        *j = p[0] + (p[2] + (p[2]&1)) / 2;
        #pragma omp section
        *i = p[2];
    }
}

/*# convert even-r offset to cube
x = q - (r + (r&1)) / 2
z = r
y = -x-z*/

void even_r_to_cube(int* p, int i, int j)
{
    #pragma omp parallel sections shared(c0, c1, c2)
    {
        p[0] = j - (i + (i&1)) / 2;
        #pragma omp section
        p[2] = i;
    }
    p[1] = -p[0] - p[2];
}

float sq_cube_euclidian(int* p0, int* p1)
{
    float result;
    int i;
    #pragma omp parallel for reduction(+:result)
    for (i = 0; i < 3; i++)
    {
        result += ((p0[i] - p1[i]) * (p0[i] - p1[i]));
    }
    return result;
}
