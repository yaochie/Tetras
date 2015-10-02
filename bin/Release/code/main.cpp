#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "globals.h"
#include "functions.h"
#include "constants.h"
#include "gamestates.h"
#include "game.h"
#include "timer.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

int main(int argc, char *args[])
{
    srand(time(NULL));

    //Initialization
	if (!init())
		return 1;
	if (!load_files())
		return 1;

    //Sets initial state
    stateID = STATE_INTRO;
    currentState = new Intro();

    //Game loop
    while (stateID != STATE_EXIT)
    {
        currentState->handle_events();
        currentState->logic();
        change_state();
        currentState->render();

        if (SDL_Flip(screen) == -1)
            return 1;
    }

    clean_up();

    //logger.close();

	return 0;
}
