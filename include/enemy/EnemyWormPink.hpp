//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMPINK_HPP
#define ALIENADVENTURE_ENEMYWORMPINK_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyWormPink : public Enemy {
public:
    EnemyWormPink(Game *game, const sf::IntRect spawnArea);

    EnemyWormPink(const EnemyWormPink &original);

    ~EnemyWormPink() override;

    virtual EnemyWormPink& operator=(const EnemyWormPink &original);

    EnemyWormPink* clone() const override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYWORMPINK_HPP
