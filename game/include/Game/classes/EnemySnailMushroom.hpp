//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP
#define ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP

#include "game/interfaces/IEnemy.hpp"

#include <memory>

class Animation;

class EnemySnailMushroom : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemySnailMushroom(const EnemySnailMushroom &original);

    EnemySnailMushroom& operator=(const EnemySnailMushroom &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemySnailMushroom(IGame *game, const sf::IntRect &spawnArea);

    ~EnemySnailMushroom() override;
};


#endif //ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP
