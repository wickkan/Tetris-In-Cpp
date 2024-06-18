#include "tetromino.h"
#include <iostream>

Tetromino::Tetromino()
{
    // Initialize a tetromino shape, for example, the "T" shape
    blocks = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
    color = {0xFF, 0x00, 0xFF, 0xFF};
    std::cout << "Tetromino created." << std::endl;
}

bool Tetromino::canMove(int dx, int dy, const int board[20][10])
{
    for (const auto &block : blocks)
    {
        int newX = block.x + dx;
        int newY = block.y + dy;
        if (newX < 0 || newX >= 10 || newY < 0 || newY >= 20 || board[newY][newX] != 0)
        {
            return false;
        }
    }
    return true;
}

void Tetromino::move(int dx, int dy, const int board[20][10])
{
    if (canMove(dx, dy, board))
    {
        for (auto &block : blocks)
        {
            block.x += dx;
            block.y += dy;
        }
    }
}

void Tetromino::rotate(const int board[20][10])
{
    // Implement rotation logic with collision detection
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
