//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMGREEN_HPP
#define ALIENADVENTURE_ENEMYWORMGREEN_HPP

#include "../interfaces/IEnemy.hpp"

#include <memory>

class Animation;

class EnemyWormGreen : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemyWormGreen(const EnemyWormGreen &original);

    EnemyWormGreen& operator=(const EnemyWormGreen &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemyWormGreen(IGame *game, const sf::IntRect &spawnArea);

    ~EnemyWormGreen() override;
};


#endif //ALIENADVENTURE_ENEMYWORMGREEN_HPP
