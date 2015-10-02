#ifndef TETRAD_H
#define TETRAD_H

#include <vector>
#include "gamestates.h"
#include "game.h"

struct coords
{
    int x, y;
};

class Tetrad
{
    public:
        virtual void handle_input() = 0;
        virtual void rotate() = 0;
        virtual void move() = 0;
        virtual void show() = 0;
};

class L : public Tetrad
{
    private:
        std::vector<coords> blocks;
        Uint32 LCol;
        std::vector<coords>::iterator it;
    public:
        L();
        ~L();
        void handle_input();
        void rotate();
        void move();
        void show();
};

#endif
