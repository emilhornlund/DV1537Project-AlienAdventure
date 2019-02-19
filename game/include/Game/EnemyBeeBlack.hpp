//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEEBLACK_HPP
#define ALIENADVENTURE_ENEMYBEEBLACK_HPP

#include <Game/IEnemy.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class EnemyBeeBlack : public IEnemy {
    private:
        std::shared_ptr<CGL::Animation> m_movingAnimation;

        std::shared_ptr<CGL::Animation> m_deadAnimation;

        EnemyBeeBlack(const EnemyBeeBlack &original);

        EnemyBeeBlack &operator=(const EnemyBeeBlack &original);

        const CGL::Animation &getMovingAnimation() const override;

        const CGL::Animation &getDeadAnimation() const override;
    public:
        EnemyBeeBlack(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~EnemyBeeBlack() override;
    };
}

#endif //ALIENADVENTURE_ENEMYBEEBLACK_HPP
