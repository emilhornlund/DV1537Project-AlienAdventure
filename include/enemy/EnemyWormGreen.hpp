//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYWORMGREEN_HPP
#define ALIENADVENTURE_ENEMYWORMGREEN_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyWormGreen : public Enemy {
private:
    EnemyWormGreen(const EnemyWormGreen &original);

    EnemyWormGreen& operator=(const EnemyWormGreen &original);
public:
    EnemyWormGreen(Game *game, const sf::IntRect spawnArea);

    ~EnemyWormGreen() override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYWORMGREEN_HPP
