//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLECOIN_HPP
#define ALIENADVENTURE_COLLECTIBLECOIN_HPP

#include "Core.hpp"
#include "Collectible.hpp"

class CollectibleCoin : public Collectible {
public:
    CollectibleCoin(Game *game, const sf::IntRect spawnArea);

    CollectibleCoin(const CollectibleCoin &original);

    ~CollectibleCoin() override;

    virtual CollectibleCoin& operator=(const CollectibleCoin &original);

    CollectibleCoin* clone() const override;

    void restore(const bool respawn) override;
};

#endif //ALIENADVENTURE_COLLECTIBLECOIN_HPP
