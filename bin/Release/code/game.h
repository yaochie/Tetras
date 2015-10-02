#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "gamestates.h"
#include "timer.h"
#include <vector>
#include <string>

enum BlockColours
{
    BLUE,
    GREEN,
    RED,
    YELLOW,
    PINK,
    CYAN,
    PURPLE,
    EMPTY,
};

enum TetradTypes
{
    L,
    J,
    S,
    Z,
    O,
    T,
    I,
};

enum RotateStates
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

struct Block
{
    bool isOccupied;
    int colour;
    int blockNum;
};

struct coords
{
    int x, y;
    //coords (int Xco, int Yco) : x(Xco), y(Yco) {};
};

extern std::vector< std::vector<coords> > LBlocks, JBlocks, SBlocks, ZBlocks, OBlocks, TBlocks, IBlocks;

class Tetrad
{
    private:
        std::vector< std::vector<coords> > shapeBlocks;
        std::vector<coords> relCoords, absCoords;
        Uint32 tetCol;
        int colour, tetType, rotState;
        std::vector<coords>::iterator it;
        int vel;
        coords centre;
        bool toRotate;
    public:
        Tetrad(int type);
        ~Tetrad();
        void handle_input();
        void rotate(std::vector<Block> *stage);
        void move_RL(std::vector<Block> *stage);
        bool move_down(std::vector<Block> *stage);
        void show();
        std::vector<coords> *get_coords();
        int get_colour();
        coords get_actual_coords(std::vector<coords>::iterator relative);
        coords wall_kick(int rotationState);
        bool check_potential_collision(int rotationState, std::vector<Block> *stage);
        bool to_rotate();
};

extern std::vector<Block> stageBlocks;

class Game : public GameState
{
    private:
        SDL_Rect stage;
        std::vector<Block>::iterator it;
        SDL_Rect blockFill;
        Tetrad *currentTet;
        Timer deltaDown, deltaRL;
        int slowDownInterval, RLInterval, quickDownInterval, actualDownInterval;
        int linesCleared, currentScore, currentLevel;
        bool gameOver, pause, moveRL;
    public:
        Game();
        ~Game();
        void handle_events();
        void logic();
        void render();
        void set_new_tet();
        void init_rotations();
        int line_check();
        void show_score();
        void show_lines();
        void show_level();
        void show_game_over();
        void show_pause();
};

#endif
