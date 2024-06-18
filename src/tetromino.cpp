#include "tetromino.h"
#include <iostream>

Tetromino::Tetromino()
{
    // Initialize a tetromino shape, for example, the "T" shape
    blocks = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
    color = {0xFF, 0x00, 0xFF, 0xFF};
    std::cout << "Tetromino created." << std::endl;
}

void Tetromino::rotate()
{
    // Rotate the tetromino
}

void Tetromino::move(int dx, int dy)
{
    for (auto &block : blocks)
    {
        block.x += dx;
        block.y += dy;
    }
}

void Tetromino::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (const auto &block : blocks)
    {
        SDL_Rect rect = {block.x * 30, block.y * 30, 30, 30};
        SDL_RenderFillRect(renderer, &rect);
    }
    std::cout << "Tetromino rendered." << std::endl;
}
