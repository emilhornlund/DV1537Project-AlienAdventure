/**
 * @file World.cpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#include <cmath>

#include "World.hpp"
#include "TileMap.hpp"
#include "Background.hpp"
#include "Game.hpp"
#include "AnimationHandler.hpp"
#include "LevelHandler.hpp"

World::World(Game *game, const sf::Vector2i worldSize, const sf::Vector2i tileSize) : GameObject(game, true) {
    this->worldSize = worldSize;
    this->tileSize = tileSize;

    this->collidableMapSize = (unsigned int)this->worldSize.x * (unsigned int)this->worldSize.y;
    this->collidableMap = new int[this->collidableMapSize];

    this->setDepth(TILELAYER_DEPTH);
    this->setPosition({0, 0});
}

World::~World() {
    this->clearCollidableMap();
}

void World::clearCollidableMap() {
    delete[] this->collidableMap;
    this->collidableMap = nullptr;
}

void World::addBackground(Background* background) {
    std::string rpath = "./resources/Backgrounds.png";
    if (!background->loadTextureFromFile(rpath)) {
        throw "Failed to load " + rpath;
    } else {
        background->setOrigin(0, 0);
        background->setOffset({0, (float)this->getGame()->getLevelHandler()->getWorldSize().y - Background::SIZE.y});
        background->generate();
        this->getAnimationHandler()->addStaticFrame(background);
    }
}

void World::addTileMap(TileMap* tileMap, int depth) {
    std::string rpath = "./resources/" + tileMap->getFilename();
    if (!tileMap->loadTextureFromFile(rpath)) {
        throw "Failed to load " + rpath;
    } else {
        tileMap->setOrigin(0, 0);
        tileMap->generate();
        if (depth == 0) {
            for (int i = 0; i < tileMap->getRows(); i++) {
                for (int j = 0; j < tileMap->getColumns(); j++) {
                    unsigned int index = i * tileMap->getColumns() + j;
                    this->collidableMap[index] = (tileMap->getData()[index] > 0) ? 1 : 0;
                }
            }
        }
        this->getAnimationHandler()->addStaticFrame(tileMap);
    }
}

sf::Vector2f World::getShortestCollisionDistance(const sf::Vector2f position) {
    int shortestIndex = -1;
    int shortestDistance = -1;

    for (int i = 0; i < this->collidableMapSize; i++) {
        bool collidable = this->collidableMap[i] > 0;
        if (collidable) {
            int col = i % this->worldSize.x;
            int row = i / this->worldSize.x;

            float posX = col * this->tileSize.x + this->tileSize.x/2;
            float posY = row * this->tileSize.y + this->tileSize.y/2;

            float diffX = std::abs(posX - position.x);
            float diffY = std::abs(posY - position.y);
            float distance = (float)std::sqrt(std::pow(diffX, 2) + std::pow(diffY, 2));

            if (distance < shortestDistance || shortestDistance < 0) {
                shortestIndex = i;
                shortestDistance = (int)distance;
            }
        }
    }

    sf::Vector2f distance;
    distance.x = (shortestIndex % this->worldSize.x) * this->tileSize.x + this->tileSize.x/2 - position.x;
    distance.y = (shortestIndex / this->worldSize.x) * this->tileSize.y + this->tileSize.y/2 - position.y;
    return distance;
}

sf::Vector2i World::getTileSize() const {
    return this->tileSize;
}

void World::restore(const bool respawn) {

}

void World::processEvents() {

}

void World::update(const float dt) {

}

