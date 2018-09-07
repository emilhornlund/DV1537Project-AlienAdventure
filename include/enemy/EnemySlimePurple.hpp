//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
#define ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemySlimePurple : public Enemy {
private:
    EnemySlimePurple(const EnemySlimePurple &original);

    EnemySlimePurple& operator=(const EnemySlimePurple &original);
public:
    EnemySlimePurple(Game *game, const sf::IntRect spawnArea);

    ~EnemySlimePurple() override;

    void configure() override;
};

#endif //ALIENADVENTURE_ENEMYSLIMEPURPLE_HPP
