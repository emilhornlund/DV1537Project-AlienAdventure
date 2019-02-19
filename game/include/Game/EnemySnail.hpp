//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSNAIL_HPP
#define ALIENADVENTURE_ENEMYSNAIL_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemySnail : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemySnail(const EnemySnail &original);

        EnemySnail &operator=(const EnemySnail &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemySnail(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemySnail() override;
    };
}

#endif //ALIENADVENTURE_ENEMYSNAIL_HPP
