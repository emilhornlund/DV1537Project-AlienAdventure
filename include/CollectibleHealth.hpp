//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
#define ALIENADVENTURE_COLLECTIBLEHEALTH_HPP

#include "Core.hpp"
#include "Collectible.hpp"

class CollectibleHealth : public Collectible {
public:
    CollectibleHealth(Game *game, const sf::IntRect spawnArea);

    CollectibleHealth(const CollectibleHealth &original);

    ~CollectibleHealth() override;

    virtual CollectibleHealth& operator=(const CollectibleHealth &original);

    CollectibleHealth* clone() const override;

    void restore(const bool respawn) override;
};

#endif //ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
