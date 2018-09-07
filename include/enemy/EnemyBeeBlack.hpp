//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEEBLACK_HPP
#define ALIENADVENTURE_ENEMYBEEBLACK_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyBeeBlack : public Enemy {
private:
    EnemyBeeBlack(const EnemyBeeBlack &original);

    EnemyBeeBlack& operator=(const EnemyBeeBlack &original);
public:
    EnemyBeeBlack(Game *game, const sf::IntRect spawnArea);

    ~EnemyBeeBlack() override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYBEEBLACK_HPP
