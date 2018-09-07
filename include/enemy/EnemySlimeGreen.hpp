//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
#define ALIENADVENTURE_ENEMYSLIMEGREEN_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySlimeGreen : public Enemy {
private:
    EnemySlimeGreen(const EnemySlimeGreen &original);

    EnemySlimeGreen& operator=(const EnemySlimeGreen &original);
public:
    EnemySlimeGreen(Game *game, const sf::IntRect spawnArea);

    ~EnemySlimeGreen() override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYSLIMEGREEN_HPP
