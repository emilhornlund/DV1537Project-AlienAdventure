/**
 * @file LevelHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef LEVEL_HANDLER_HPP
#define LEVEL_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class LevelHandler {
private:
    Game* game;

    sf::Vector2i worldSize;

    unsigned int readNextInt(std::ifstream &file) const;

    std::string readNextString(std::ifstream &file) const;
public:
    explicit LevelHandler(Game* game);

    ~LevelHandler();

    sf::Vector2i getWorldSize() const;

    void load();
};

#endif /* LevelHandler_h */
