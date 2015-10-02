#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "functions.h"
#include "globals.h"
#include "constants.h"
#include "gamestates.h"
#include "game.h"

//Blits surface to screen
void apply_surface (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

//Initialization
bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;

	if (TTF_Init() == -1)
		return false;

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (screen == NULL)
		return false;

	SDL_WM_SetCaption("Tetris", NULL);

	return true;
}

//loads necessary files
bool load_files()
{
    font = TTF_OpenFont("Eurosti.ttf", 48);
    fontSmall = TTF_OpenFont("Eurosti.ttf", 24);

    return true;
}

//Frees memory, quits
void clean_up()
{
    TTF_CloseFont(font);
    TTF_CloseFont(fontSmall);
    TTF_Quit();

    SDL_Quit();
}

//set the next state to change to
void set_next_state(int newState)
{
    if (nextState != STATE_EXIT)
        nextState = newState;
}

//changes the state
void change_state()
{
    if (nextState != STATE_NULL)
    {
        if (nextState != STATE_EXIT)
            delete currentState;

        switch (nextState)
        {
            case STATE_INTRO:
                currentState = new Intro();
                break;
            case STATE_GAME:
                currentState = new Game();
                break;
            case STATE_HELP:
                currentState = new Help();
                break;
            case STATE_CREDITS:
                currentState = new Credits();
                break;
            default:
                break;
        }

        stateID = nextState;
        nextState = STATE_NULL;
    }
}
