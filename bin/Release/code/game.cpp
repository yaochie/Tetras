#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "game.h"
#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "timer.h"
#include <vector>
#include <sstream>

std::vector< std::vector<coords> > LBlocks, JBlocks, SBlocks, ZBlocks, OBlocks, TBlocks, IBlocks;

//---------------------------------------
//Game gamestate

//initializes, eg main gamestage
std::vector<Block> stageBlocks;

Game::Game()
{
    init_rotations();

    stage.w = BLOCK_WIDTH * STAGE_BLOCK_WIDTH;
    stage.h = SCREEN_HEIGHT;
    stage.x = (SCREEN_WIDTH - stage.w)/2;
    stage.y = 0;

    Block initial;
    initial.isOccupied = false;
    initial.colour = EMPTY;
    for (int i=0; i<STAGE_BLOCK_HEIGHT*STAGE_BLOCK_WIDTH; i++)
    {
        initial.blockNum = i;
        stageBlocks.push_back(initial);
    }

    set_new_tet();
    slowDownInterval = 800;
    quickDownInterval = 15;
    RLInterval = 75;
    actualDownInterval = slowDownInterval;

    linesCleared = 0;
    currentScore = 0;
    currentLevel = 1;
    gameOver = false;
    pause = false;

    deltaRL.start();
    deltaDown.start();
}

Game::~Game()
{
}

//set all block rotation states
void Game::init_rotations()
{
    std::vector<coords> relativeBlocks;
    coords block1, block2, block3, block4;

    //L
    block1.x = -1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = -1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = -1; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 1; relativeBlocks.push_back(block4);
    LBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = -1; relativeBlocks.push_back(block2);
    block3.x = -1; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = -1; block4.y = 0; relativeBlocks.push_back(block4);
    LBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = -1; relativeBlocks.push_back(block4);
    LBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 1; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = 1; block4.y = 0; relativeBlocks.push_back(block4);
    LBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();

    //J
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 1; relativeBlocks.push_back(block4);
    JBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 1; relativeBlocks.push_back(block2);
    block3.x = -1; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = -1; block4.y = 0; relativeBlocks.push_back(block4);
    JBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = -1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = -1; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = -1; relativeBlocks.push_back(block4);
    JBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = -1; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 1; block4.y = 0; relativeBlocks.push_back(block4);
    JBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();

    //S
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = -1; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = -1; block4.y = 0; relativeBlocks.push_back(block4);
    SBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 0; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 1; block4.y = 1; relativeBlocks.push_back(block4);
    SBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = 0; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = -1; block4.y = 1; relativeBlocks.push_back(block4);
    SBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = -1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 1; relativeBlocks.push_back(block4);
    SBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();

    //Z
    block1.x = -1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = -1; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 1; block4.y = 0; relativeBlocks.push_back(block4);
    ZBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 1; relativeBlocks.push_back(block4);
    ZBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 1; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = -1; block4.y = 0; relativeBlocks.push_back(block4);
    ZBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = -1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = -1; relativeBlocks.push_back(block4);
    ZBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();

    //O
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 0; relativeBlocks.push_back(block4);
    OBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 0; relativeBlocks.push_back(block4);
    OBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 0; relativeBlocks.push_back(block4);
    OBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 0; relativeBlocks.push_back(block4);
    OBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();

    //T
    block1.x = 1; block1.y = 0; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = -1; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = -1; relativeBlocks.push_back(block4);
    TBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 0; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = 1; block4.y = 0; relativeBlocks.push_back(block4);
    TBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = 0; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = -1; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 1; relativeBlocks.push_back(block4);
    TBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 0; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = -1; relativeBlocks.push_back(block3);
    block4.x = -1; block4.y = 0; relativeBlocks.push_back(block4);
    TBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();

    //I
    block1.x = 0; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 0; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = 0; block4.y = 2; relativeBlocks.push_back(block4);
    IBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = 0; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = 0; relativeBlocks.push_back(block3);
    block4.x = 2; block4.y = 0; relativeBlocks.push_back(block4);
    IBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = 1; block1.y = -1; relativeBlocks.push_back(block1);
    block2.x = 1; block2.y = 0; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = 1; block4.y = 2; relativeBlocks.push_back(block4);
    IBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
    block1.x = -1; block1.y = 1; relativeBlocks.push_back(block1);
    block2.x = 0; block2.y = 1; relativeBlocks.push_back(block2);
    block3.x = 1; block3.y = 1; relativeBlocks.push_back(block3);
    block4.x = 2; block4.y = 1; relativeBlocks.push_back(block4);
    IBlocks.push_back(relativeBlocks);
    relativeBlocks.clear();
}

void Game::handle_events()
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
                    case SDLK_DOWN:
                        actualDownInterval = quickDownInterval;
                        break;
                    case SDLK_p:
                        if (!gameOver)
                        {
                            if (pause)
                                pause = false;
                            else
                                pause = true;
                        }
                        break;
                    case SDLK_ESCAPE:
                        set_next_state(STATE_INTRO);
                        break;
                    default:
                        break;
                }

                moveRL = true;
                currentTet->handle_input();
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_DOWN)
                    actualDownInterval = slowDownInterval;

                currentTet->handle_input();
                break;
            default:
                break;
        }
    }
}

void Game::logic()
{
    if (!gameOver && !pause)
    {
        if (currentTet->to_rotate())
        {
            currentTet->rotate(&stageBlocks);
        }
        //if it's time for the block to move, move it
        if (deltaRL.get_ticks() > RLInterval || moveRL)
        {
            moveRL = false;
            currentTet->move_RL(&stageBlocks);
            deltaRL.start();
        }

        if (deltaDown.get_ticks() > actualDownInterval)
        {
            if (currentTet->move_down(&stageBlocks))
            {
                //collision, so stop this, transfer to stageBlocks, open new tetrad
                //first check if any part of the tet is above the stage. if yes, game over
                std::vector<coords> *fill = currentTet->get_coords();
                std::vector<coords>::iterator it2;
                for (it2=fill->begin(); it2<fill->end(); it2++)
                {
                    if ((*it2).y >= 0)
                    {
                        stageBlocks.at((*it2).x + (*it2).y * STAGE_BLOCK_WIDTH).isOccupied = true;
                        stageBlocks.at((*it2).x + (*it2).y * STAGE_BLOCK_WIDTH).colour = currentTet->get_colour();
                    }
                }

                //check for a full line
                //if there is a full line, and the just landed tet would have caused gameover otherwise,
                //move the tet down
                int linesRemoved = line_check();
                if (linesRemoved != 0)
                {
                    for (it2=fill->begin(); it2<fill->end(); it2++)
                    {
                        if ((*it2).y < 0)
                        {
                            stageBlocks.at((*it2).x + ((*it2).y + linesRemoved) * STAGE_BLOCK_WIDTH).isOccupied = true;
                            stageBlocks.at((*it2).x + ((*it2).y + linesRemoved) * STAGE_BLOCK_WIDTH).colour = currentTet->get_colour();
                        }
                    }
                }

                //check if any part of the just landed tet is outside the stage
                //if yes, gameover
                for (it2=fill->begin(); it2<fill->end(); it2++)
                {
                    if (((*it2).y + linesRemoved) < 0)
                    {
                        gameOver = true;
                        break;
                    }
                }
                actualDownInterval = slowDownInterval;

                if (!gameOver)
                {
                    delete currentTet;
                    set_new_tet();
                }

                //check for game over
                std::vector<coords> *currentCoords = currentTet->get_coords();
                for (it2=currentCoords->begin(); it2<currentCoords->end(); it2++)
                {
                    if ((*it2).y >= 0)
                    {
                        if (stageBlocks.at((*it2).x + (*it2).y * STAGE_BLOCK_WIDTH).isOccupied)
                        {
                            gameOver = true;
                            break;
                        }
                    }
                }

                if (!gameOver)
                    currentScore += 10;
            }
            deltaDown.start();
        }
    }
}

void Game::render()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_FillRect(screen, &stage, SDL_MapRGB(screen->format, 50, 50, 50));

    show_score();
    show_lines();
    show_level();

    //show blocks
    for (it=stageBlocks.begin(); it<stageBlocks.end(); it++)
    {
        if ((*it).isOccupied)
        {
            blockFill.y = ((*it).blockNum / STAGE_BLOCK_WIDTH) * BLOCK_WIDTH + 1;
            blockFill.x = (((*it).blockNum % STAGE_BLOCK_WIDTH) * BLOCK_WIDTH) + stage.x + 1;
            blockFill.w = BLOCK_WIDTH - 2;
            blockFill.h = BLOCK_WIDTH - 2;
            Uint32 col;

            switch ((*it).colour)
            {
                case BLUE:
                    col = SDL_MapRGB(screen->format, 0, 0, 255);
                    break;
                case GREEN:
                    col = SDL_MapRGB(screen->format, 0, 255, 0);
                    break;
                case RED:
                    col = SDL_MapRGB(screen->format, 255, 0, 0);
                    break;
                case YELLOW:
                    col = SDL_MapRGB(screen->format, 255, 255, 0);
                    break;
                case PINK:
                    col = SDL_MapRGB(screen->format, 255, 0, 255);
                    break;
                case CYAN:
                    col = SDL_MapRGB(screen->format, 0, 255, 255);
                    break;
                case PURPLE:
                    col = SDL_MapRGB(screen->format, 160, 32, 240);
                    break;
                default:
                    break;
            }

            SDL_FillRect(screen, &blockFill, col);
        }
    }

    currentTet->show();

    if (pause)
    {
        show_pause();
    }

    if (gameOver)
    {
        show_game_over();
    }

    if (event.type == SDL_QUIT)
        delete currentTet;
}

void Game::show_lines()
{
    SDL_Surface *lines;
    std::stringstream lineScore;
    lineScore << "Lines: " << linesCleared;
    lines = TTF_RenderText_Blended(fontSmall, lineScore.str().c_str(), textColor);
    apply_surface(480, 80, lines, screen);
    SDL_FreeSurface(lines);
}

void Game::show_score()
{
    SDL_Surface *score;
    std::stringstream scoreDisp;
    scoreDisp << "Score: " << currentScore;
    score = TTF_RenderText_Blended(fontSmall, scoreDisp.str().c_str(), textColor);
    apply_surface(480, 110, score, screen);
    SDL_FreeSurface(score);
}

void Game::show_level()
{
    SDL_Surface *level;
    std::stringstream levDisp;
    levDisp << "Level: " << currentLevel;
    level = TTF_RenderText_Blended(fontSmall, levDisp.str().c_str(), textColor);
    apply_surface(480, 50, level, screen);
    SDL_FreeSurface(level);
}

void Game::show_game_over()
{
    SDL_Surface *over;
    over = TTF_RenderText_Blended(fontSmall, "Game Over!", textColor);
    apply_surface((SCREEN_WIDTH - over->w)/2, (SCREEN_HEIGHT - over->h)/2, over, screen);
    SDL_FreeSurface(over);
}

void Game::show_pause()
{
    SDL_Surface *pauseScr;
    pauseScr = TTF_RenderText_Blended(fontSmall, "Paused. Press P to resume.", textColor);
    apply_surface((SCREEN_WIDTH - pauseScr->w)/2, (SCREEN_HEIGHT - pauseScr->h)/2, pauseScr, screen);
    SDL_FreeSurface(pauseScr);
}

void Game::set_new_tet()
{
    int newTet = rand() % 7;

    switch (newTet)
    {
        case 0:
            currentTet = new Tetrad(L);
            break;
        case 1:
            currentTet = new Tetrad(J);
            break;
        case 2:
            currentTet = new Tetrad(S);
            break;
        case 3:
            currentTet = new Tetrad(Z);
            break;
        case 4:
            currentTet = new Tetrad(O);
            break;
        case 5:
            currentTet = new Tetrad(T);
            break;
        case 6:
            currentTet = new Tetrad(I);
            break;
    }
}

int Game::line_check()
{
    //check by line
    bool full;
    int removedLines = 0;
    for (int line=0; line<STAGE_BLOCK_HEIGHT; line++)
    {
        full = true;
        for (int block=0; block<STAGE_BLOCK_WIDTH; block++)
        {
            if (!stageBlocks.at(line*STAGE_BLOCK_WIDTH + block).isOccupied)
            {
                full = false;
                break;
            }
        }
        //if full, remove line and make above blocks fall
        if (full)
        {
            removedLines++;
            currentScore += 100;
            linesCleared++;
            if (linesCleared % 5 == 0)
            {
                currentLevel++;
                slowDownInterval = slowDownInterval / 1.1;
            }

            for (int aboveLine=line; aboveLine>0; aboveLine--)
            {
                for (int block=0; block<STAGE_BLOCK_WIDTH; block++)
                {
                    stageBlocks.at(aboveLine*STAGE_BLOCK_WIDTH + block).isOccupied
                    = stageBlocks.at((aboveLine-1)*STAGE_BLOCK_WIDTH + block).isOccupied;
                    stageBlocks.at(aboveLine*STAGE_BLOCK_WIDTH + block).colour
                    = stageBlocks.at((aboveLine-1)*STAGE_BLOCK_WIDTH + block).colour;
                }
            }
            //clear top line
            for (int block=0; block<STAGE_BLOCK_WIDTH; block++)
            {
                stageBlocks.at(block).isOccupied = false;
                stageBlocks.at(block).colour = EMPTY;
            }
        }
    }
    return removedLines;
}

//-----------------------------------------------------------
//Tetrads

Tetrad::Tetrad(int type)
{
    tetType = type;
    rotState = UP;
    vel = 0;
    centre.x = 4;
    centre.y = 0;
    toRotate = false;

    switch (type)
    {
        case L:
        {
            tetCol = SDL_MapRGB(screen->format, 0, 0, 255);
            colour = BLUE;
            shapeBlocks = LBlocks;
            break;
        }
        case J:
        {
            tetCol = SDL_MapRGB(screen->format, 0, 255, 0);
            colour = GREEN;
            shapeBlocks = JBlocks;
            break;
        }
        case S:
        {
            tetCol = SDL_MapRGB(screen->format, 255, 0, 0);
            colour = RED;
            shapeBlocks = SBlocks;
            break;
        }
        case Z:
        {
            tetCol = SDL_MapRGB(screen->format, 255, 255, 0);
            colour = YELLOW;
            shapeBlocks = ZBlocks;
            break;
        }
        case O:
        {
            tetCol = SDL_MapRGB(screen->format, 255, 0, 255);
            colour = PINK;
            shapeBlocks = OBlocks;
            break;
        }
        case T:
        {
            tetCol = SDL_MapRGB(screen->format, 0, 255, 255);
            colour = CYAN;
            shapeBlocks = TBlocks;
            break;
        }
        case I:
        {
            tetCol = SDL_MapRGB(screen->format, 160, 32, 240);
            colour = PURPLE;
            shapeBlocks = IBlocks;
            break;
        }
    }

    relCoords = shapeBlocks.at(UP);
}

Tetrad::~Tetrad()
{
}

void Tetrad::handle_input()
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_LEFT)
            vel = -1;
        else if (event.key.keysym.sym == SDLK_RIGHT)
            vel = 1;
        else if (event.key.keysym.sym == SDLK_UP)
        {
            toRotate = true;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_LEFT)
            vel = 0;
        else if (event.key.keysym.sym == SDLK_RIGHT)
            vel = 0;
    }
}

void Tetrad::rotate(std::vector<Block> *stage)
{
    if (centre.y < 1)
        return;

    int newRotState;

    switch (rotState)
    {
        case UP:
            newRotState = RIGHT;
            break;
        case RIGHT:
            newRotState = DOWN;
            break;
        case DOWN:
            newRotState = LEFT;
            break;
        case LEFT:
            newRotState = UP;
            break;
    }

    //check if wall-kick is required, then check for collisions. If collides, do not rotate
    coords centreShift = wall_kick(newRotState);

    if (check_potential_collision(newRotState, stage))
    {
        centre.x -= centreShift.x;
        centre.y -= centreShift.y;
        return;
    }

    relCoords.clear();
    relCoords = shapeBlocks.at(newRotState);

    rotState = newRotState;
    toRotate = false;
}

coords Tetrad::wall_kick(int rotationState)
{
    bool done = false;
    coords totalShift;
    totalShift.x = 0;
    totalShift.y = 0;

    while (!done)
    {
        done = true;
        for (it=shapeBlocks.at(rotationState).begin(); it<shapeBlocks.at(rotationState).end(); it++)
        {
            coords actualCoord(get_actual_coords(it));

            if (actualCoord.x < 0)
            {
                centre.x += 1;
                totalShift.x += 1;
                done = false;
            }
            else if (actualCoord.x >= STAGE_BLOCK_WIDTH)
            {
                centre.x -= 1;
                totalShift.x -= 1;
                done = false;
            }

            if (actualCoord.y < 0)
            {
                centre.y += 1;
                totalShift.y += 1;
                done = false;
            }
            else if (actualCoord.y >= STAGE_BLOCK_HEIGHT)
            {
                centre.y -= 1;
                totalShift.y -= 1;
                done = false;
            }
            if (!done)
                break;
        }
    }
    return totalShift;
}

bool Tetrad::check_potential_collision(int rotationState, std::vector<Block> *stage)
{
    for (it=shapeBlocks.at(rotationState).begin(); it<shapeBlocks.at(rotationState).end(); it++)
    {
        coords actualCoord(get_actual_coords(it));

        if (stage->at((actualCoord.y) * STAGE_BLOCK_WIDTH + actualCoord.x).isOccupied)
            return true;
    }

    return false;
}

void Tetrad::move_RL(std::vector<Block> *stage)
{
    if (centre.y < 1)
        return;

    if (vel > 0)
    {
        for (it=relCoords.begin(); it<relCoords.end(); it++)
        {
            coords actualCoord(get_actual_coords(it));

            if (actualCoord.x >= STAGE_BLOCK_WIDTH-1 || stage->at((actualCoord.y) * STAGE_BLOCK_WIDTH + actualCoord.x + 1).isOccupied)
                return;
        }
    }
    else if (vel < 0)
    {
        for (it=relCoords.begin(); it<relCoords.end(); it++)
        {
            coords actualCoord(get_actual_coords(it));

            if (actualCoord.x <= 0 || stage->at((actualCoord.y) * STAGE_BLOCK_WIDTH + actualCoord.x - 1).isOccupied)
                return;
        }
    }

    centre.x += vel;
}

bool Tetrad::move_down(std::vector<Block> *stage)
{
    //if no blocks below, move down, else return collision
    for (it=relCoords.begin(); it<relCoords.end(); it++)
    {
        coords actualCoord(get_actual_coords(it));

        if (actualCoord.y >= STAGE_BLOCK_HEIGHT-1 || (stage->at((actualCoord.y + 1) * STAGE_BLOCK_WIDTH + actualCoord.x)).isOccupied)
            return true;
    }
    centre.y += 1;
    return false;
}

coords Tetrad::get_actual_coords(std::vector<coords>::iterator relative)
{
    coords actualCoord;
    actualCoord.x = centre.x + relative->x;
    actualCoord.y = centre.y + relative->y;
    return actualCoord;
}

void Tetrad::show()
{
    for (it=relCoords.begin(); it<relCoords.end(); it++)
    {
        coords actualCoord(get_actual_coords(it));
        if (actualCoord.y < 0)
            continue;

        SDL_Rect blockFill;

        blockFill.x = actualCoord.x * BLOCK_WIDTH + (SCREEN_WIDTH - BLOCK_WIDTH * STAGE_BLOCK_WIDTH)/2 + 1;
        blockFill.y = actualCoord.y * BLOCK_WIDTH + 1;
        blockFill.w = BLOCK_WIDTH - 2;
        blockFill.h = BLOCK_WIDTH - 2;

        SDL_FillRect(screen, &blockFill, tetCol);
    }
}

std::vector<coords> *Tetrad::get_coords()
{
    absCoords.clear();
    for (it=relCoords.begin(); it<relCoords.end(); it++)
    {
        coords actualCoord(get_actual_coords(it));
        absCoords.push_back(actualCoord);
    }

    return &absCoords;
}

int Tetrad::get_colour()
{
    return colour;
}

bool Tetrad::to_rotate()
{
    return toRotate;
}
