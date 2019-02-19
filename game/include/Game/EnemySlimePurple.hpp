//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
#define ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemySlimePurple : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemySlimePurple(const EnemySlimePurple &original);

        EnemySlimePurple &operator=(const EnemySlimePurple &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemySlimePurple(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemySlimePurple() override;
    };
}

#endif //ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
