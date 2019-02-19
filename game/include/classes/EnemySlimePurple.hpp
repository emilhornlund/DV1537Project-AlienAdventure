//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
#define ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP

#include "../interfaces/IEnemy.hpp"

#include <memory>

class Animation;

class EnemySlimePurple : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemySlimePurple(const EnemySlimePurple &original);

    EnemySlimePurple& operator=(const EnemySlimePurple &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemySlimePurple(IGame *game, const sf::IntRect &spawnArea);

    ~EnemySlimePurple() override;
};

#endif //ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
