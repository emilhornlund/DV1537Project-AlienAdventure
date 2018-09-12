/**
 * @file World.cpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/Background.hpp"
#include "game/classes/TileMap.hpp"
#include "game/classes/World.hpp"

#include <cmath>

#include <SFML/Graphics/Texture.hpp>

World::World(IGame *game, const sf::Vector2i &worldSize, const sf::Vector2i &tileSize) : IGameObject(game, IGameObject::DRAW_ORDER_TILEMAP, true) {
    this->worldSize = worldSize;
    this->tileSize = tileSize;

    this->collidableMapSize = (unsigned int)this->worldSize.x * (unsigned int)this->worldSize.y;
    this->collidableMap = new int[this->collidableMapSize];

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
    background->setTexture(this->getGame()->getTextureResourceHandler().load("./resources/Backgrounds.png"));
    background->setOrigin(0, 0);
    background->setOffset({0, (float)this->getGame()->getPropertyHandler().get<sf::Vector2i>("worldSize").y - Background::SIZE.y});
    background->generate();
    this->addEntity(background);
}

void World::addTileMap(TileMap* tileMap, int depth) {
    tileMap->setTexture(this->getGame()->getTextureResourceHandler().load("./resources/" + tileMap->getFilename()));
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
    this->addEntity(tileMap);
}

sf::Vector2f World::getShortestCollisionDistance(const sf::Vector2f &position) {
    int shortestIndex = -1;
    int shortestDistance = -1;

    for (int i = 0; i < this->collidableMapSize; i++) {
        bool collidable = this->collidableMap[i] > 0;
        if (collidable) {
            int col = i % this->worldSize.x;
            int row = i / this->worldSize.x;

            float posX = col * this->tileSize.x + (float)this->tileSize.x/2;
            float posY = row * this->tileSize.y + (float)this->tileSize.y/2;

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

