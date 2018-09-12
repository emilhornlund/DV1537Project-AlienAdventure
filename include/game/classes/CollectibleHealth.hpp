//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
#define ALIENADVENTURE_COLLECTIBLEHEALTH_HPP

#include "game/interfaces/ICollectible.hpp"

#include <memory>

class Animation;

class CollectibleHealth : public ICollectible {
private:
    std::shared_ptr<Animation> m_animation;

    CollectibleHealth(const CollectibleHealth &original);

    CollectibleHealth& operator=(const CollectibleHealth &original);
public:
    CollectibleHealth(IGame *game, const sf::IntRect &spawnArea);

    ~CollectibleHealth() override;

    void restore(const bool respawn) override;
};

#endif //ALIENADVENTURE_COLLECTIBLEHEALTH_HPP
