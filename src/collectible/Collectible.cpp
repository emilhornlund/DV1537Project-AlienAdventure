/**
 * @file Collectible.cpp
 * @date 2016-12-09
 * @author Emil Hörnlund
 */

#include "collectible/Collectible.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "Game.hpp"
#include "ResourceHandler.hpp"

#include <random>

float FLOATING_VELOCITY = 20;

Collectible::Collectible(Game *game, const sf::IntRect spawnArea, const std::string &soundFilePath) : GameObject(game,
                                                                                                                 true) {
    this->spawnArea = spawnArea;

    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(soundFilePath))
        this->getGame()->getSoundBufferResourceHandler()->load(soundFilePath);
    this->soundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(soundFilePath);

    this->sound = new sf::Sound;
    this->sound->setBuffer(*this->soundBuffer);

    sf::Vector2f position = {(float)spawnArea.left + (float)spawnArea.width/2, (float)spawnArea.top + spawnArea.height/2};
    this->setPosition(position);
}

Collectible::~Collectible() {
    delete this->sound;
    this->sound = nullptr;
}

bool Collectible::isCollected() const {
    return this->collected;
}

void Collectible::setCollected(const bool collected) {
    this->collected = collected;
    if (collected) {
        this->getAnimationHandler()->clearSequences();
        this->sound->play();
    }
}

void Collectible::processEvents() { }

void Collectible::update(const float dt) {
    sf::Vector2f velocity = this->getVelocity();
    sf::Vector2f position = this->getPosition();

    float minY, maxY;
    minY = (float)this->spawnArea.top;
    maxY = (float)(this->spawnArea.top + this->spawnArea.height - this->spawnArea.height / 1.5);

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
