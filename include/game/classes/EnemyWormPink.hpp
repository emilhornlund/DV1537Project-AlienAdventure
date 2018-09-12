//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMPINK_HPP
#define ALIENADVENTURE_ENEMYWORMPINK_HPP

#include "game/interfaces/IEnemy.hpp"

#include <memory>

class Animation;

class EnemyWormPink : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemyWormPink(const EnemyWormPink &original);

    EnemyWormPink& operator=(const EnemyWormPink &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemyWormPink(IGame *game, const sf::IntRect &spawnArea);

    ~EnemyWormPink() override;
};


#endif //ALIENADVENTURE_ENEMYWORMPINK_HPP
