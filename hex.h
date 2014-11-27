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
    Temperature temp;
    int whoWantsMore;
    Temperature wantValue;
} Hexagon;


/*# convert cube to even-r offset
q = x + (z + (z&1)) / 2
r = z*/

void cube_to_even_r(int* p, int* i, int *j);

/*# convert even-r offset to cube
x = q - (r + (r&1)) / 2
z = r
y = -x-z*/

void even_r_to_cube(int* p, int i, int j);

float sq_cube_euclidian(int* p0, int* p1);


#endif
