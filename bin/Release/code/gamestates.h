#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <vector>

enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_GAME,
    STATE_HELP,
    STATE_CREDITS,
    STATE_EXIT,
};

class GameState
{
    public:
        virtual void handle_events() = 0;
        virtual void logic() = 0;
        virtual void render() = 0;
        virtual ~GameState() {};
};

class Intro : public GameState
{
    private:
        SDL_Surface *title, *help, *creds;
    public:
        Intro();
        ~Intro();
        void handle_events();
        void logic();
        void render();
};

class Help : public GameState
{
    private:
        SDL_Surface *up, *down, *lr, *esc, *pse;
    public:
        Help();
        ~Help();
        void handle_events();
        void logic();
        void render();
};

class Credits : public GameState
{
    private:
        SDL_Surface *ft, *lib, *auth;
    public:
        Credits();
        ~Credits();
        void handle_events();
        void logic();
        void render();
};

#endif
