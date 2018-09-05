//
// Created by Emil Hörnlund on 2018-09-05.
//

#ifndef ALIENADVENTURE_ENEMYBEEBLACK_HPP
#define ALIENADVENTURE_ENEMYBEEBLACK_HPP

#include "Core.hpp"
#include "Enemy.hpp"

class EnemyBeeBlack : public Enemy {
public:
    EnemyBeeBlack(Game *game, const sf::IntRect spawnArea);

    EnemyBeeBlack(const EnemyBeeBlack &original);

    ~EnemyBeeBlack() override;

    virtual EnemyBeeBlack& operator=(const EnemyBeeBlack &original);

    EnemyBeeBlack* clone() const override;

    void configure() override;
};


#endif //ALIENADVENTURE_ENEMYBEEBLACK_HPP
