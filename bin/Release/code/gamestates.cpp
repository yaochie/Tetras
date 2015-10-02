#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "gamestates.h"
#include <cstdlib>

//-------------------------------------------
//Intro gamestate

Intro::Intro()
{
    title = TTF_RenderText_Blended(font, "Press Space to start.", textColor);
    creds = TTF_RenderText_Blended(fontSmall, "Credits: C", textColor);
    help = TTF_RenderText_Blended(fontSmall, "Help: H", textColor);
}

Intro::~Intro()
{
    SDL_FreeSurface(title);
    SDL_FreeSurface(creds);
    SDL_FreeSurface(help);
}

void Intro::handle_events()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                set_next_state(STATE_EXIT);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        set_next_state(STATE_EXIT);
                        break;
                    case SDLK_SPACE:
                        set_next_state(STATE_GAME);
                        break;
                    case SDLK_h:
                        set_next_state(STATE_HELP);
                        break;
                    case SDLK_c:
                        set_next_state(STATE_CREDITS);
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void Intro::logic()
{
}

void Intro::render()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    apply_surface((SCREEN_WIDTH - title->w)/2, (SCREEN_HEIGHT - title->h)/2, title, screen);
    apply_surface(30, 420, help, screen);
    apply_surface(500, 420, creds, screen);
}

Help::Help()
{
    up = TTF_RenderText_Blended(fontSmall, "Up - Rotate", textColor);
    down = TTF_RenderText_Blended(fontSmall, "Down - Quickdrop", textColor);
    lr = TTF_RenderText_Blended(fontSmall, "Left/Right - Move", textColor);
    esc = TTF_RenderText_Blended(fontSmall, "Escape - Back", textColor);
    pse = TTF_RenderText_Blended(fontSmall, "P - Pause", textColor);
}

Help::~Help()
{
    SDL_FreeSurface(up);
    SDL_FreeSurface(down);
    SDL_FreeSurface(lr);
    SDL_FreeSurface(esc);
    SDL_FreeSurface(pse);
}

void Help::handle_events()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                set_next_state(STATE_EXIT);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    set_next_state(STATE_INTRO);
                break;
            default:
                break;
        }
    }
}

void Help::logic()
{
}

void Help::render()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    apply_surface(30, 30, lr, screen);
    apply_surface(30, 60, up, screen);
    apply_surface(30, 90, down, screen);
    apply_surface(30, 210, esc, screen);
    apply_surface(30, 150, pse, screen);
}

Credits::Credits()
{
    lib = TTF_RenderText_Blended(fontSmall, "Created with SDL 1.2.15 and SDL_ttf.", textColor);
    ft = TTF_RenderText_Blended(fontSmall, "Font: Eurostile.", textColor);
    SDL_Color nameColor = {0x11, 0x11, 0x11};
    auth = TTF_RenderText_Blended(fontSmall, "Made by Yao Chong", nameColor);
}

Credits::~Credits()
{
    SDL_FreeSurface(ft);
    SDL_FreeSurface(lib);
    SDL_FreeSurface(auth);
}

void Credits::handle_events()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                set_next_state(STATE_EXIT);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    set_next_state(STATE_INTRO);
                break;
            default:
                break;
        }
    }
}

void Credits::logic()
{
}

void Credits::render()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    apply_surface((SCREEN_WIDTH - lib->w)/2, (SCREEN_HEIGHT - lib->h)/2 - 40, lib, screen);
    apply_surface((SCREEN_WIDTH - ft->w)/2, (SCREEN_HEIGHT - ft->h)/2 + 40, ft, screen);
    apply_surface((SCREEN_WIDTH*3/2 - auth->w)/2, SCREEN_HEIGHT - 80, auth, screen);
}
