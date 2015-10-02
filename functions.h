#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL/SDL.h"
#include "gamestates.h"
#include <vector>
#include <string>
#include <list>

void apply_surface (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

bool init();
bool load_files();

void clean_up();

void set_next_state(int newState);
void change_state();

void save_high_scores(std::list<std::string> *names, std::list<int> *scores);
void load_high_scores(std::list<std::string> *names, std::list<int> *scores);
#endif
