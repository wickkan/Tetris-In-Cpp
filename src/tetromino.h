#pragma once
#include "SDL.h"
#include <vector>

class Tetromino
{
public:
    Tetromino();
    void rotate();
    void move(int dx, int dy);
    void render(SDL_Renderer *renderer);

private:
    std::vector<SDL_Point> blocks;
    SDL_Color color;
};
