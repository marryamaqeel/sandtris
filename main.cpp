#include "Game.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    Game myGame;
    myGame.run();

    return 0;
}