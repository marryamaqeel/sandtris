#include "Game.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    // Seed random numbers once at the start of the program
    srand(time(NULL));

    // Create the toybox and hit play!
    Game myGame;
    myGame.run();

    return 0;
}