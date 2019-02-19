/**
 * @file Collectible.cpp
 * @date 2016-12-09
 * @author Emil Hörnlund
 */

#include <Core/ResourceHandler.hpp>

#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/ICollectible.hpp>

#include <random>
#include <functional>

float FLOATING_VELOCITY = 20;

AA::ICollectible::ICollectible(CGL::IGame *game, const sf::IntRect &spawnArea, const std::string &soundFilePath) : IGameObject(game, GameScene::DRAW_ORDER_COLLECTIBLE, true) {
    this->m_spawnArea = spawnArea;

    this->m_soundBuffer = &this->getGame()->getSoundBufferResourceHandler().load(soundFilePath);

    this->m_sound = std::make_shared<sf::Sound>();
    this->m_sound->setBuffer(*this->m_soundBuffer);

    sf::Vector2f position = {(float)spawnArea.left + (float)spawnArea.width/2, (float)spawnArea.top + spawnArea.height/2};
    this->setPosition(position);
}

AA::ICollectible::~ICollectible() = default;

bool AA::ICollectible::isCollected() const {
    return this->m_collected;
}

void AA::ICollectible::setCollected(const bool collected) {
    this->m_collected = collected;
    if (collected) {
        this->clearEntities();
        this->m_sound->play();
    }
}

void AA::ICollectible::processEvents() { }

void AA::ICollectible::update(const float dt) {
    sf::Vector2f velocity = this->getVelocity();
    sf::Vector2f position = this->getPosition();

    float minY, maxY;
    minY = (float)this->m_spawnArea.top;
    maxY = (float)(this->m_spawnArea.top + this->m_spawnArea.height - this->m_spawnArea.height / 1.5);

    auto rand = std::bind(std::uniform_int_distribution<>(0,20),std::default_random_engine(std::random_device{}()));

    if (velocity.y == 0) {
        velocity.y = (rand() % 20 < 10) ? FLOATING_VELOCITY : -FLOATING_VELOCITY;
        float randPos = minY + (rand() % (int)(maxY-minY));
        position.y = randPos;
    }
    if (velocity.y < 0 && position.y < minY) {
        velocity.y = FLOATING_VELOCITY;
    }
    if (velocity.y > 0 && position.y > maxY) {
        velocity.y = -FLOATING_VELOCITY;
    }

    position.y += velocity.y * dt;
    this->setVelocity(velocity);
    this->setPosition(position);
}
