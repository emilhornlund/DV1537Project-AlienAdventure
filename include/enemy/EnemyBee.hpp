//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEE_HPP
#define ALIENADVENTURE_ENEMYBEE_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyBee : public Enemy {
private:
    EnemyBee(const EnemyBee &original);

    EnemyBee& operator=(const EnemyBee &original);
public:
    EnemyBee(Game *game, const sf::IntRect spawnArea);

    ~EnemyBee() override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYBEE_HPP
