//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP
#define ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySnailMushroom : public Enemy {
public:
    EnemySnailMushroom(Game *game, const sf::IntRect spawnArea);

    EnemySnailMushroom(const EnemySnailMushroom &original);

    ~EnemySnailMushroom() override;

    virtual EnemySnailMushroom& operator=(const EnemySnailMushroom &original);

    EnemySnailMushroom* clone() const override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYSNAILMUSHROOM_HPP
