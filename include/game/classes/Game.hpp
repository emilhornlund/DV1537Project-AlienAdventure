/**
 * @file Game.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "core/interfaces/IGame.hpp"

#include <memory>

class Game : public IGame {
private:
    Game(const Game &original);

    Game& operator=(const Game &original);
public:
    Game();

    ~Game() override;
};

#endif /* Game_hpp */
