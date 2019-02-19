//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLECOIN_HPP
#define ALIENADVENTURE_COLLECTIBLECOIN_HPP

#include <Game/ICollectible.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class CollectibleCoin : public ICollectible {
    private:
        std::shared_ptr<CGL::Animation> m_animation;

        CollectibleCoin(const CollectibleCoin &original);

        CollectibleCoin &operator=(const CollectibleCoin &original);
    public:
        CollectibleCoin(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~CollectibleCoin() override;

        void restore(const bool respawn) override;
    };
}

#endif //ALIENADVENTURE_COLLECTIBLECOIN_HPP
