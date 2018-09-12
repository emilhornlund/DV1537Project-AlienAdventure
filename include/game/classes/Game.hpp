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
