//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "core/classes/AnimatedEntity.hpp"
#include "core/classes/Animation.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/EnemyBee.hpp"

#include <SFML/Graphics/Texture.hpp>

EnemyBee::EnemyBee(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({5, 21, 55, 48});

    int posY = 65 * 6;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("./resources/Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("./resources/Enemies.png"));
}

EnemyBee::~EnemyBee() = default;

const Animation &EnemyBee::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemyBee::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
