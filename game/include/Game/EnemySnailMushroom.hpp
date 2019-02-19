//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP
#define ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemySnailMushroom : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemySnailMushroom(const EnemySnailMushroom &original);

        EnemySnailMushroom &operator=(const EnemySnailMushroom &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemySnailMushroom(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemySnailMushroom() override;
    };
}

#endif //ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP
