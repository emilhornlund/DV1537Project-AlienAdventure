//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEBLUE_HPP
#define ALIENADVENTURE_ENEMYSLIMEBLUE_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemySlimeBlue : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemySlimeBlue(const EnemySlimeBlue &original);

        EnemySlimeBlue &operator=(const EnemySlimeBlue &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemySlimeBlue(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemySlimeBlue() override;
    };
}

#endif //ALIENADVENTURE_ENEMYSLIMEBLUE_HPP
