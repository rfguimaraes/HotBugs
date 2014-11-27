#include "hex.h"

/*# convert cube to even-r offset
q = x + (z + (z&1)) / 2
r = z*/

void cube_to_even_r(int x, int y, int z, int* i, int *j)
{
    *j = x + (z + (z&1)) / 2;
    *i = z;
}

/*# convert even-r offset to cube
x = q - (r + (r&1)) / 2
z = r
y = -x-z*/

void even_r_to_cube(int* x, int* y, int* z, int i, int j)
{
    *x = j - (i + (i&1)) / 2;
    *z = i;
    *y = -(*x) - (*z);
}

float cube_euclidian(int x0, int y0, int z0, int x1, int y1, int z1)
{
    int c0, c1, c2;
    #pragma omp parallel sections shared(c0, c1, c2)
    {
        c0 = (x0 - x1) * (x0 - x1);
        #pragma omp section
        c1 = (y0 - y1) * (y0 - y1);
        #pragma omp section
        c2 = (z0 - z1) * (z0 - z1);
    }
    return sqrt(c0 + c1 + c2)
}
