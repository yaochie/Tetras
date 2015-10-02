#include "timer.h"
#include "SDL/SDL.h"

Timer::Timer()
{
    startTicks = 0;
    started = false;
}

void Timer::start()
{
    startTicks = SDL_GetTicks();
    started = true;
}

int Timer::get_ticks()
{
    return (SDL_GetTicks() - startTicks);
}
