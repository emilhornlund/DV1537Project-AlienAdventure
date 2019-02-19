//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/classes/AnimatedEntity.hpp>
#include <Core/classes/Animation.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/interfaces/IGame.hpp>

#include <Game/classes/EnemySlimeGreen.hpp>

#include <SFML/Graphics/Texture.hpp>

EnemySlimeGreen::EnemySlimeGreen(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({8, 31, 49, 34});

    int posY = 65 * 1;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*2, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*3, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemySlimeGreen::~EnemySlimeGreen() = default;

const Animation &EnemySlimeGreen::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemySlimeGreen::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
