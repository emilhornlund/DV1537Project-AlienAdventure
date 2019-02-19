//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/classes/AnimatedEntity.hpp>
#include <Core/classes/Animation.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/interfaces/IGame.hpp>

#include <Game/classes/EnemyWormPink.hpp>

#include <SFML/Graphics/Texture.hpp>

EnemyWormPink::EnemyWormPink(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({4, 43, 57, 22});

    int posY = 65 * 14;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemyWormPink::~EnemyWormPink() = default;

const Animation &EnemyWormPink::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemyWormPink::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
