//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSNAIL_HPP
#define ALIENADVENTURE_ENEMYSNAIL_HPP

#include "../interfaces/IEnemy.hpp"

#include <memory>

class Animation;

class EnemySnail : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemySnail(const EnemySnail &original);

    EnemySnail& operator=(const EnemySnail &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemySnail(IGame *game, const sf::IntRect &spawnArea);

    ~EnemySnail() override;
};


#endif //ALIENADVENTURE_ENEMYSNAIL_HPP
