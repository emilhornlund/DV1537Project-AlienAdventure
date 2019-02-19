//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/classes/AnimatedEntity.hpp>
#include <Core/classes/Animation.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/interfaces/IGame.hpp>

#include <Game/classes/EnemyWormGreen.hpp>

#include <SFML/Graphics/Texture.hpp>

EnemyWormGreen::EnemyWormGreen(IGame *game, const sf::IntRect &spawnArea) : IEnemy(game, spawnArea) {
    this->setBoundingBox({4, 43, 57, 22});

    int posY = 65 * 13;

    this->m_movingAnimation = std::make_shared<Animation>();
    this->m_movingAnimation->addFrame({65*0, posY, 65, 65});
    this->m_movingAnimation->addFrame({65*1, posY, 65, 65});
    this->m_movingAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));

    this->m_deadAnimation = std::make_shared<Animation>();
    this->m_deadAnimation->addFrame({65*2, posY, 65, 65});
    this->m_deadAnimation->setSpriteSheet(game->getTextureResourceHandler().load("Enemies.png"));
}

EnemyWormGreen::~EnemyWormGreen() = default;

const Animation &EnemyWormGreen::getMovingAnimation() const {
    return *this->m_movingAnimation;
}

const Animation &EnemyWormGreen::getDeadAnimation() const {
    return *this->m_deadAnimation;
}
