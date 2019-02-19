//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMGREEN_HPP
#define ALIENADVENTURE_ENEMYWORMGREEN_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemyWormGreen : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemyWormGreen(const EnemyWormGreen &original);

        EnemyWormGreen &operator=(const EnemyWormGreen &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemyWormGreen(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemyWormGreen() override;
    };
}

#endif //ALIENADVENTURE_ENEMYWORMGREEN_HPP
