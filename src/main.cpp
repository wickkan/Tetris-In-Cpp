#include "game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    std::srand(std::time(0)); // Initialize random seed once
    Game game;
    if (game.init())
    {
        game.run();
    }
    game.cleanup();
    return 0;
}
