//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
#define ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySlimePurple : public Enemy {
public:
    EnemySlimePurple(Game *game, const sf::IntRect spawnArea);

    EnemySlimePurple(const EnemySlimePurple &original);

    ~EnemySlimePurple() override;

    virtual EnemySlimePurple& operator=(const EnemySlimePurple &original);

    EnemySlimePurple* clone() const override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
