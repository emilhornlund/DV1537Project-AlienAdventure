//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "core/classes/AnimatedEntity.hpp"
#include "core/classes/Animation.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/EnemyBeeBlack.hpp"

#include <SFML/Graphics/Texture.hpp>

EnemyBeeBlack::EnemyBeeBlack(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({5, 21, 55, 48});

    int posY = 65 * 7;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemyBeeBlack::~EnemyBeeBlack() = default;

const Animation &EnemyBeeBlack::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemyBeeBlack::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
