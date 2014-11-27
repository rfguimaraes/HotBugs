#ifndef HEX_H_INCLUDED
#define HEX_H_INCLUDED

#include <math.h>

typedef float Temperature;

typedef struct 
{
    char bug;
    int heat, cold;
    unsigned int seed;
    int lastUpdated;
    Temperature temperature;
    int whoWantsMore;
    Temperature wantValue;
} Hexagon;


/*# convert cube to even-r offset
q = x + (z + (z&1)) / 2
r = z*/

void cube_to_even_r(int x, int y, int z, int* i, int *j);

/*# convert even-r offset to cube
x = q - (r + (r&1)) / 2
z = r
y = -x-z*/

void even_r_to_cube(int* x, int* y, int* z, int i, int j);

float cube_euclidian(int x0, int y0, int z0, int x1, int y1, int z1);


#endif
