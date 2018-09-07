//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMPINK_HPP
#define ALIENADVENTURE_ENEMYWORMPINK_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyWormPink : public Enemy {
private:
    EnemyWormPink(const EnemyWormPink &original);

    EnemyWormPink& operator=(const EnemyWormPink &original);
public:
    EnemyWormPink(Game *game, const sf::IntRect spawnArea);

    ~EnemyWormPink() override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYWORMPINK_HPP
