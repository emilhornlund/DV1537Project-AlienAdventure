//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
#define ALIENADVENTURE_ENEMYSLIMEGREEN_HPP

#include <Game/interfaces/IEnemy.hpp>

#include <memory>

class Animation;

class EnemySlimeGreen : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemySlimeGreen(const EnemySlimeGreen &original);

    EnemySlimeGreen& operator=(const EnemySlimeGreen &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemySlimeGreen(IGame *game, const sf::IntRect &spawnArea);

    ~EnemySlimeGreen() override;
};


#endif //ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
