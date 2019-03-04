// Nigel Lipps
//  The @ kills the robots
//  main.cpp

#include "Game.h"
#include <ctime>            //time
#include <stdlib.h>         //srand and rand

int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 80);
    // Play the game
    g.play();
}


