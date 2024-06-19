#include "game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), lastTick(0), tickInterval(500), score(0),
               currentTetromino(Tetromino()), nextTetromino(Tetromino())
{
    // Initialize board
    for (int y = 0; y < 20; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            board[y][x] = 0;
        }
    }
    std::cout << "Game object created." << std::endl;
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
    std::cout << "Initialization successful." << std::endl;
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
    std::cout << "Cleanup done." << std::endl;
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
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                currentTetromino.move(-1, 0, board);
                break;
            case SDLK_RIGHT:
                currentTetromino.move(1, 0, board);
                break;
            case SDLK_DOWN:
                currentTetromino.move(0, 1, board);
                break;
            case SDLK_UP:
                currentTetromino.rotate(board);
                break;
            }
        }
    }
}

void Game::update()
{
    Uint32 currentTick = SDL_GetTicks();
    if (currentTick > lastTick + tickInterval)
    {
        if (currentTetromino.canMove(0, 1, board))
        {
            currentTetromino.move(0, 1, board);
        }
        else
        {
            // Lock tetromino in place
            for (const auto &block : currentTetromino.blocks)
            {
                board[block.y][block.x] = 1; // Mark as filled
            }
            clearLines(); // Clear any full lines

            // Create a new tetromino and check for game over
            currentTetromino = nextTetromino;
            nextTetromino = Tetromino();
            if (!currentTetromino.canMove(0, 0, board))
            {
                isRunning = false; // Game over
                std::cout << "Game Over!" << std::endl;
            }
        }
        lastTick = currentTick;
    }
    // Additional game logic
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    // Render the board
    for (int y = 0; y < 20; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            if (board[y][x] != 0)
            {
                SDL_Rect rect = {x * 30, y * 30, 30, 30};
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White color for occupied cells
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // Render the current tetromino
    currentTetromino.render(renderer);

    // Render the next tetromino
    SDL_Rect previewArea = {350, 50, 100, 100};               // Adjust position and size as needed
    SDL_SetRenderDrawColor(renderer, 0x44, 0x44, 0x44, 0xFF); // Grey background for preview area
    SDL_RenderFillRect(renderer, &previewArea);
    nextTetromino.render(renderer); // You may need to adjust positions within the preview area

    // Render the score
    // For simplicity, we will just print the score to the console
    std::cout << "Score: " << score << std::endl;

    SDL_RenderPresent(renderer);
    std::cout << "Rendered frame." << std::endl;
}

void Game::reset()
{
    // Reset the game state
}

void Game::clearLines()
{
    for (int y = 0; y < 20; ++y)
    {
        bool lineFull = true;
        for (int x = 0; x < 10; ++x)
        {
            if (board[y][x] == 0)
            {
                lineFull = false;
                break;
            }
        }
        if (lineFull)
        {
            // Clear line and move everything above it down
            for (int ty = y; ty > 0; --ty)
            {
                for (int tx = 0; tx < 10; ++tx)
                {
                    board[ty][tx] = board[ty - 1][tx];
                }
            }
            for (int tx = 0; tx < 10; ++tx)
            {
                board[0][tx] = 0;
            }
            score += 100;                                    // Increase score
            tickInterval = std::max(100, tickInterval - 10); // Decrease interval to increase speed, min 100ms
        }
    }
}
