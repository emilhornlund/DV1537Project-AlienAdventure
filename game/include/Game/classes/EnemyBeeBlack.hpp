//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEEBLACK_HPP
#define ALIENADVENTURE_ENEMYBEEBLACK_HPP

#include <Game/interfaces/IEnemy.hpp>

#include <memory>

class Animation;

class EnemyBeeBlack : public IEnemy {
private:
    std::shared_ptr<Animation> m_movingAnimation;

    std::shared_ptr<Animation> m_deadAnimation;

    EnemyBeeBlack(const EnemyBeeBlack &original);

    EnemyBeeBlack& operator=(const EnemyBeeBlack &original);

    const Animation& getMovingAnimation() const override;

    const Animation& getDeadAnimation() const override;
public:
    EnemyBeeBlack(IGame *game, const sf::IntRect &spawnArea);

    ~EnemyBeeBlack() override;
};


#endif //ALIENADVENTURE_ENEMYBEEBLACK_HPP
