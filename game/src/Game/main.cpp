/**
 * @file main.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Game/Game.hpp>

int main(int, char const**) {
    AA::Game* game = new AA::Game();
    int exitCode = game->run();
    delete game;
    return exitCode;
}
