//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLECOIN_HPP
#define ALIENADVENTURE_COLLECTIBLECOIN_HPP

#include "Core.hpp"
#include "Collectible.hpp"

class CollectibleCoin : public Collectible {
private:
    CollectibleCoin(const CollectibleCoin &original);

    CollectibleCoin& operator=(const CollectibleCoin &original);
public:
    CollectibleCoin(Game *game, const sf::IntRect spawnArea);

    ~CollectibleCoin() override;

    void restore(const bool respawn) override;
};

#endif //ALIENADVENTURE_COLLECTIBLECOIN_HPP
