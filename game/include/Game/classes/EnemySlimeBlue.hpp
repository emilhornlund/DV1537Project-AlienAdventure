//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEBLUE_HPP
#define ALIENADVENTURE_ENEMYSLIMEBLUE_HPP

#include <Game/interfaces/IEnemy.hpp>

#include <memory>

class Animation;

class EnemySlimeBlue : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemySlimeBlue(const EnemySlimeBlue &original);

    EnemySlimeBlue& operator=(const EnemySlimeBlue &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemySlimeBlue(IGame *game, const sf::IntRect &spawnArea);

    ~EnemySlimeBlue() override;
};

#endif //ALIENADVENTURE_ENEMYSLIMEBLUE_HPP
