//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSNAIL_HPP
#define ALIENADVENTURE_ENEMYSNAIL_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySnail : public Enemy {
private:
    EnemySnail(const EnemySnail &original);

    EnemySnail& operator=(const EnemySnail &original);
public:
    EnemySnail(Game *game, const sf::IntRect spawnArea);

    ~EnemySnail() override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYSNAIL_HPP
