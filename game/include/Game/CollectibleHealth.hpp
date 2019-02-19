//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
#define ALIENADVENTURE_COLLECTIBLEHEALTH_HPP

#include <Game/ICollectible.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class CollectibleHealth : public ICollectible {
    private:
        std::shared_ptr<CGL::Animation> m_animation;

        CollectibleHealth(const CollectibleHealth &original);

        CollectibleHealth &operator=(const CollectibleHealth &original);
    public:
        CollectibleHealth(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~CollectibleHealth() override;

        void restore(const bool respawn) override;
    };
}

#endif //ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
