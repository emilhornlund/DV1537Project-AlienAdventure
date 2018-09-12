//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLECOIN_HPP
#define ALIENADVENTURE_COLLECTIBLECOIN_HPP

#include "game/interfaces/ICollectible.hpp"

#include <memory>

class Animation;

class CollectibleCoin : public ICollectible {
private:
    std::shared_ptr<Animation> m_animation;

    CollectibleCoin(const CollectibleCoin &original);

    CollectibleCoin& operator=(const CollectibleCoin &original);
public:
    CollectibleCoin(IGame *game, const sf::IntRect &spawnArea);

    ~CollectibleCoin() override;

    void restore(const bool respawn) override;
};

#endif //ALIENADVENTURE_COLLECTIBLECOIN_HPP
