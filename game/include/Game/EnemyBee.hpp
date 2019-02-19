//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEE_HPP
#define ALIENADVENTURE_ENEMYBEE_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemyBee : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemyBee(const EnemyBee &original);

        EnemyBee &operator=(const EnemyBee &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemyBee(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemyBee() override;
    };
}

#endif //ALIENADVENTURE_ENEMYBEE_HPP
