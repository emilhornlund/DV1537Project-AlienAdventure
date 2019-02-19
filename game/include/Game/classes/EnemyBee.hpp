//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEE_HPP
#define ALIENADVENTURE_ENEMYBEE_HPP

#include <Game/interfaces/IEnemy.hpp>

#include <memory>

class Animation;

class EnemyBee : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemyBee(const EnemyBee &original);

    EnemyBee &operator=(const EnemyBee &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemyBee(IGame *game, const sf::IntRect &spawnArea);

    ~EnemyBee() override;
};

#endif //ALIENADVENTURE_ENEMYBEE_HPP
