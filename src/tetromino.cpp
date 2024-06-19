#include "tetromino.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

Tetromino::Tetromino()
{
    std::srand(std::time(0)); // Initialize random seed
    int shapeType = std::rand() % 7;

    switch (shapeType)
    {
    case 0: // I shape
        blocks = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
        color = {0x00, 0xFF, 0xFF, 0xFF}; // Cyan
        break;
    case 1: // O shape
        blocks = {{1, 0}, {2, 0}, {1, 1}, {2, 1}};
        color = {0xFF, 0xFF, 0x00, 0xFF}; // Yellow
        break;
    case 2: // T shape
        blocks = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
        color = {0xFF, 0x00, 0xFF, 0xFF}; // Magenta
        break;
    case 3: // S shape
        blocks = {{1, 0}, {2, 0}, {0, 1}, {1, 1}};
        color = {0x00, 0xFF, 0x00, 0xFF}; // Green
        break;
    case 4: // Z shape
        blocks = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        color = {0xFF, 0x00, 0x00, 0xFF}; // Red
        break;
    case 5: // J shape
        blocks = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
        color = {0x00, 0x00, 0xFF, 0xFF}; // Blue
        break;
    case 6: // L shape
        blocks = {{2, 0}, {0, 1}, {1, 1}, {2, 1}};
        color = {0xFF, 0xA5, 0x00, 0xFF}; // Orange
        break;
    }
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

bool Tetromino::canRotate(const int board[20][10])
{
    std::vector<SDL_Point> rotatedBlocks(blocks);
    SDL_Point pivot = blocks[1]; // Using the second block as pivot for simplicity
    for (auto &block : rotatedBlocks)
    {
        int x = block.x - pivot.x;
        int y = block.y - pivot.y;
        int newX = pivot.x - y;
        int newY = pivot.y + x;
        if (newX < 0 || newX >= 10 || newY < 0 || newY >= 20 || board[newY][newX] != 0)
        {
            return false;
        }
    }
    return true;
}

void Tetromino::rotate(const int board[20][10])
{
    if (canRotate(board))
    {
        SDL_Point pivot = blocks[1]; // Using the second block as pivot for simplicity
        for (auto &block : blocks)
        {
            int x = block.x - pivot.x;
            int y = block.y - pivot.y;
            block.x = pivot.x - y;
            block.y = pivot.y + x;
        }
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
