#pragma once
#include "SDL.h"
#include "tetromino.h"
#include <vector>

class Game
{
public:
    Game();
    bool init();
    void run();
    void cleanup();

private:
    void processInput();
    void update();
    void render();
    void reset();
    void clearLines();

    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isRunning;
    bool isPaused;
    int board[20][10];
    int score;
    Tetromino currentTetromino;
    Tetromino nextTetromino;
    Uint32 lastTick;
    Uint32 tickInterval;
};
