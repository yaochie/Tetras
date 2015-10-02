#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "gamestates.h"
#include <fstream>
#include <string>

extern SDL_Surface *screen;

extern SDL_Event event;

extern TTF_Font *font;
extern TTF_Font *fontSmall;

extern SDL_Color textColor;

extern int stateID;
extern int nextState;

extern GameState *currentState;

//extern std::ofstream logger;
//void log(std::string message);

#endif

