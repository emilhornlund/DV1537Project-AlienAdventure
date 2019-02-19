/**
 * @file World.cpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>

#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/TileMap.hpp>
#include <Game/World.hpp>

#include <cmath>

#include <SFML/Graphics/Texture.hpp>

AA::World::World(CGL::IGame *game, const sf::Vector2i &worldSize, const sf::Vector2i &tileSize) : CGL::IGameObject(game, GameScene::DRAW_ORDER_TILEMAP, true) {
    this->worldSize = worldSize;
    this->tileSize = tileSize;

    this->collidableMapSize = (unsigned int)this->worldSize.x * (unsigned int)this->worldSize.y;
    this->collidableMap = new int[this->collidableMapSize];

    this->setPosition({0, 0});
}

AA::World::~World() {
    this->clearCollidableMap();
}

void AA::World::clearCollidableMap() {
    delete[] this->collidableMap;
    this->collidableMap = nullptr;
}

void AA::World::addTileMap(std::shared_ptr<TileMap> tileMap, int depth) {
    tileMap->setTexture(this->getGame()->getTextureResourceHandler().load(tileMap->getFilename()));
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

sf::Vector2f AA::World::getShortestCollisionDistance(const sf::Vector2f &position) {
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
    distance.x = (shortestIndex % this->worldSize.x) * this->tileSize.x + this->tileSize.x/2.f - position.x;
    distance.y = (shortestIndex / this->worldSize.x) * this->tileSize.y + this->tileSize.y/2.f - position.y;
    return distance;
}

sf::Vector2i AA::World::getTileSize() const {
    return this->tileSize;
}

void AA::World::restore(const bool respawn) {

}

void AA::World::processEvents() {

}

void AA::World::update(const float dt) {

}

