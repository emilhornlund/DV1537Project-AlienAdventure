/**
 * @file World.hpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_WORLD_HPP
#define ALIENADVENTURE_WORLD_HPP

#include <Core/IGameObject.hpp>

namespace AA { //AlienAdventure
    class TileMap;

    class World : public CGL::IGameObject {
    private:
        sf::Vector2i worldSize;

        sf::Vector2i tileSize;

        unsigned int collidableMapSize;

        int *collidableMap;

        World(const World &original);

        World &operator=(const World &original);

        void clearCollidableMap();
    public:
        World(CGL::IGame *game, const sf::Vector2i &worldSize, const sf::Vector2i &tileSize);

        ~World() override;

        void addTileMap(std::shared_ptr<TileMap> tileMap, int depth);

        sf::Vector2f getShortestCollisionDistance(const sf::Vector2f &position);

        sf::Vector2i getTileSize() const;

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif /* ALIENADVENTURE_WORLD_HPP */
