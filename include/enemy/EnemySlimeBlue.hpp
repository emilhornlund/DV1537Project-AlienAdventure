//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEBLUE_HPP
#define ALIENADVENTURE_ENEMYSLIMEBLUE_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySlimeBlue : public Enemy {
private:
    EnemySlimeBlue(const EnemySlimeBlue &original);

    EnemySlimeBlue& operator=(const EnemySlimeBlue &original);
public:
    EnemySlimeBlue(Game *game, const sf::IntRect spawnArea);

    ~EnemySlimeBlue() override;

    void configure() override;
};

#endif //ALIENADVENTURE_ENEMYSLIMEBLUE_HPP
