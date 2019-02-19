//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
#define ALIENADVENTURE_ENEMYSLIMEGREEN_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemySlimeGreen : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemySlimeGreen(const EnemySlimeGreen &original);

        EnemySlimeGreen &operator=(const EnemySlimeGreen &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemySlimeGreen(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemySlimeGreen() override;
    };
}

#endif //ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
