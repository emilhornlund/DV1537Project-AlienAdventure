/**
 * @file main.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "Game.hpp"
#include "EventHandler.hpp"

int main(int, char const**) {
    auto seed = (unsigned)time(0);
    srand(seed);

    Game *game = new Game;
    int exitCode = game->run();
    delete game;
    
    return exitCode;
}
