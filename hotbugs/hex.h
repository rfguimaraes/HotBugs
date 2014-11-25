#ifndef HEX_H_INCLUDED
#define HEX_H_INCLUDED

typedef float Temperature;

typedef enum
{
    NORMAL, BUG, FIRE, ICE 
    /*ROCK, GROUND, STEEL, DRAGON, FAIRY, WATER, PSYCHIC, FLYING, FIGHTING,
     * GHOST, DARK, ELECTRIC, GRASS */
} Entity;

typedef struct 
{
    Entity entity;
    unsigned int seed;
    int lastUpdated;
    Temperature temperature;
    int whoWantsMore;
    float wantValue;
} Hexagon;

#endif
