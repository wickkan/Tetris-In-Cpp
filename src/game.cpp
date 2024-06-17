#include "game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), lastTick(0), tickInterval(500)
{
    // Initialize board
    for (int y = 0; y < 20; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            board[y][x] = 0;
        }
    }
}

bool Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    isRunning = true;
    return true;
}

void Game::run()
{
    while (isRunning)
    {
        processInput();
        update();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}

void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::processInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        // Handle other events like keyboard input for moving and rotating tetrominoes
    }
}

void Game::update()
{
    Uint32 currentTick = SDL_GetTicks();
    if (currentTick > lastTick + tickInterval)
    {
        // Move tetromino down
        lastTick = currentTick;
    }
    // Additional game logic like collision detection
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    // Render the board and the current tetromino

    SDL_RenderPresent(renderer);
}

void Game::reset()
{
    // Reset the game state
}
