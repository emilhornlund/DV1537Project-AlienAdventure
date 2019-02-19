//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/AnimatedEntity.hpp>
#include <Core/Animation.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/IGame.hpp>

#include <Game/EnemySnailMushroom.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::EnemySnailMushroom::EnemySnailMushroom(CGL::IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({3, 25, 59, 40});

    int posY = 65 * 9;

    this->m_movingAnimation = std::make_shared<CGL::Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<CGL::Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

AA::EnemySnailMushroom::~EnemySnailMushroom() = default;

const CGL::Animation &AA::EnemySnailMushroom::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const CGL::Animation &AA::EnemySnailMushroom::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
