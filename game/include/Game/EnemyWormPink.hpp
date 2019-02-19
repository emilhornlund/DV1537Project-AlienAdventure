//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMPINK_HPP
#define ALIENADVENTURE_ENEMYWORMPINK_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemyWormPink : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemyWormPink(const EnemyWormPink &original);

        EnemyWormPink &operator=(const EnemyWormPink &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemyWormPink(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemyWormPink() override;
    };
}

#endif //ALIENADVENTURE_ENEMYWORMPINK_HPP
