//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "../../../lib/include/classes/AnimatedEntity.hpp"
#include "../../../lib/include/classes/Animation.hpp"
#include "../../../lib/include/classes/ResourceHandler.hpp"
#include "../../../lib/include/interfaces/IGame.hpp"
#include "../../include/classes/EnemySlimeBlue.hpp"

#include <SFML/Graphics/Texture.hpp>

EnemySlimeBlue::EnemySlimeBlue(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({8, 31, 49, 34});

    int posY = 65 * 2;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*2, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*3, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemySlimeBlue::~EnemySlimeBlue() = default;

const Animation &EnemySlimeBlue::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemySlimeBlue::getDeadAnimation() const {
    return *this->m_deadAnimation;
}