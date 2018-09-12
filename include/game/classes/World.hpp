/**
 * @file World.hpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#ifndef WORLD_HPP
#define WORLD_HPP

#include "core/interfaces/IGameObject.hpp"

class Background;
class TileMap;

class World : public IGameObject {
private:
    sf::Vector2i worldSize;

    sf::Vector2i tileSize;

    unsigned int collidableMapSize;

    int* collidableMap;

    World(const World &original);

    World& operator=(const World &original);

    void clearCollidableMap();
public:
    World(IGame *game, const sf::Vector2i &worldSize, const sf::Vector2i &tileSize);

    ~World() override;

    void addBackground(Background* background);

    void addTileMap(TileMap* tileMap, int depth);

    sf::Vector2f getShortestCollisionDistance(const sf::Vector2f &position);

    sf::Vector2i getTileSize() const;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* World_hpp */
