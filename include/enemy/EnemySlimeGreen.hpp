//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
#define ALIENADVENTURE_ENEMYSLIMEGREEN_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySlimeGreen : public Enemy {
public:
    EnemySlimeGreen(Game *game, const sf::IntRect spawnArea);

    EnemySlimeGreen(const EnemySlimeGreen &original);

    ~EnemySlimeGreen() override;

    virtual EnemySlimeGreen& operator=(const EnemySlimeGreen &original);

    EnemySlimeGreen* clone() const override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
