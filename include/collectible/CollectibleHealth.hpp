//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
#define ALIENADVENTURE_COLLECTIBLEHEALTH_HPP

#include "Core.hpp"
#include "Collectible.hpp"

class CollectibleHealth : public Collectible {
private:
    CollectibleHealth(const CollectibleHealth &original);

    CollectibleHealth& operator=(const CollectibleHealth &original);
public:
    CollectibleHealth(Game *game, const sf::IntRect spawnArea);

    ~CollectibleHealth() override;

    void restore(const bool respawn) override;
};

#endif //ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
