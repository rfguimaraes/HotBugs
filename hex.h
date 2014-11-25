#ifndef HEX_H_INCLUDED
#define HEX_H_INCLUDED

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

#endif
