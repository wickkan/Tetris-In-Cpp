#pragma once
#include "SDL.h"
#include <vector>

class Tetromino
{
public:
    Tetromino();
    void rotate(const int board[20][10]);
    void move(int dx, int dy, const int board[20][10]);
    void render(SDL_Renderer *renderer);
    bool canMove(int dx, int dy, const int board[20][10]);

    std::vector<SDL_Point> blocks;
    SDL_Color color;

private:
    bool canRotate(const int board[20][10]);
};
