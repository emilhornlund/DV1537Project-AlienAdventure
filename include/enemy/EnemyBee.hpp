//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEE_HPP
#define ALIENADVENTURE_ENEMYBEE_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyBee : public Enemy {
public:
    EnemyBee(Game *game, const sf::IntRect spawnArea);

    EnemyBee(const EnemyBee &original);

    ~EnemyBee() override;

    virtual EnemyBee& operator=(const EnemyBee &original);

    EnemyBee* clone() const override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYBEE_HPP
