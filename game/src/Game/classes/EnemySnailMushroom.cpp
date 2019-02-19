//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "../../../lib/include/classes/AnimatedEntity.hpp"
#include "../../../lib/include/classes/Animation.hpp"
#include "../../../lib/include/classes/ResourceHandler.hpp"
#include "../../../lib/include/interfaces/IGame.hpp"
#include "../../include/classes/EnemySnailMushroom.hpp"

#include <SFML/Graphics/Texture.hpp>

EnemySnailMushroom::EnemySnailMushroom(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({3, 25, 59, 40});

    int posY = 65 * 9;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemySnailMushroom::~EnemySnailMushroom() = default;

const Animation &EnemySnailMushroom::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemySnailMushroom::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
