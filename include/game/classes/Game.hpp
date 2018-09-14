/**
 * @file Game.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System/Clock.hpp>

#include "core/interfaces/IGame.hpp"

class Game : public IGame {
public:
    static const int DRAW_ORDER_HUD = 0;
    static const int DRAW_ORDER_ENEMY_DEAD = 1;
    static const int DRAW_ORDER_PLAYER = 2;
    static const int DRAW_ORDER_ENEMY_ALIVE = 3;
    static const int DRAW_ORDER_COLLECTIBLE = 4;
    static const int DRAW_ORDER_CLOUD_LAYER1 = 5;
    static const int DRAW_ORDER_TILEMAP = 6;
    static const int DRAW_ORDER_CLOUD_LAYER2 = 7;
    static const int DRAW_ORDER_BACKGROUND = 8;
    static const int DRAW_ORDER_SUN = 9;
private:
    Game(const Game &original);

    Game& operator=(const Game &original);

    unsigned int readNextInt(std::ifstream &file) const;

    std::string readNextString(std::ifstream &file) const;
public:
    Game();

    ~Game() override;

    void loadLevel() override;
};

#endif /* Game_hpp */
