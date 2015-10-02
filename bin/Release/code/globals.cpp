#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "globals.h"
#include <fstream>
#include <string>

SDL_Surface *screen = NULL;

SDL_Event event;

TTF_Font *font;
TTF_Font *fontSmall;

SDL_Color textColor = {0xFF, 0xFF, 0xFF};

int stateID = STATE_NULL;
int nextState = STATE_NULL;

GameState *currentState = NULL;

/*
std::ofstream logger("log.txt");
void log(std::string message)
{
    logger << message << std::endl;
    logger.flush();
}*/
