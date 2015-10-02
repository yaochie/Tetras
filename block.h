#ifndef BLOCK_H
#define BLOCK_H

enum BlockColours
{
    BLUE,
    GREEN,
    RED,
    YELLOW,
    ORANGE,
    LIGHT_BLUE,
};

struct Block
{
    bool isOccupied;
    int Colour;
};

#endif
