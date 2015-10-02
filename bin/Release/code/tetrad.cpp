#include "SDL/SDL.h"
#include "tetrad.h"
#include <vector>
#include "gamestates.h"
#include "constants.h"
#include "globals.h"

L::L()
{
    LCol = SDL_MapRGB(screen->format, 0, 0, 255);

    blocks.push_back({3,0});
    blocks.push_back({3,1});
    blocks.push_back({3,2});
    blocks.push_back({4,2});
}

L::~L()
{
}

void L::handle_input()
{
}

void L::rotate()
{
}

void L::move()
{
    //if no blocks below, move down
    for (it=blocks.begin(); it<blocks.end(); it++)
    {
        (*it).y += 1;
    }
}

void L::show()
{
    for (it=blocks.begin(); it<blocks.end(); it++)
    {
        SDL_Rect blockFill;

        blockFill.y = ((*it).y / STAGE_BLOCK_WIDTH) * BLOCK_WIDTH + 1;
        blockFill.x = (((*it).x % STAGE_BLOCK_WIDTH) * BLOCK_WIDTH) + (SCREEN_WIDTH - BLOCK_WIDTH * STAGE_BLOCK_WIDTH)/2 + 1;
        blockFill.w = BLOCK_WIDTH - 2;
        blockFill.h = BLOCK_WIDTH - 2;

        SDL_FillRect(screen, &blockFill, LCol);
    }
}
