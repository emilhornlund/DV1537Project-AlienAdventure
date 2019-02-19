//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "../../../lib/include/classes/AnimatedEntity.hpp"
#include "../../../lib/include/classes/Animation.hpp"
#include "../../../lib/include/classes/ResourceHandler.hpp"
#include "../../../lib/include/interfaces/IGame.hpp"
#include "../../include/classes/EnemyBee.hpp"

#include <SFML/Graphics/Texture.hpp>

EnemyBee::EnemyBee(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({5, 21, 55, 48});

    int posY = 65 * 6;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemyBee::~EnemyBee() = default;

const Animation &EnemyBee::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemyBee::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
