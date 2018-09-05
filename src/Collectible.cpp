/**
 * @file Collectible.cpp
 * @date 2016-12-09
 * @author Emil Hörnlund
 */

#include "Collectible.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "Game.hpp"
#include "ResourceHandler.hpp"

const std::string COIN_SEQUENCE_ID = "Coin";
const std::string LIFE_SEQUENCE_ID = "Life";

float FLOATING_VELOCITY = 20;

Collectible::Collectible(Game *game, const sf::IntRect spawnArea, const Collectible::CollectibleType type) : GameObject(game) {
    this->spawnArea = spawnArea;
    this->type = type;
    this->setBoundingBox({ 10, 10, 50, 50 });

    std::string rpath;
    switch (this->type) {
        case CollectibleType::GoldCoin:
            rpath = "./resources/Coin.wav";
            break;
        case CollectibleType::Life:
            rpath = "./resources/Health.wav";
            break;
    }

    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->soundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);

    this->sound = new sf::Sound;
    this->sound->setBuffer(*this->soundBuffer);

    sf::Vector2f position = {(float)spawnArea.left + (float)spawnArea.width/2, (float)spawnArea.top + spawnArea.height/2};
    this->setPosition(position);
}

Collectible::Collectible(const Collectible &original) : GameObject(original) {
    this->type = original.type;
    this->spawnArea = original.spawnArea;
    this->collected = original.collected;

    this->soundBuffer = new sf::SoundBuffer(*original.soundBuffer);
    this->sound = new sf::Sound(*original.sound);
    this->sound->setBuffer(*this->soundBuffer);
}

Collectible::~Collectible() {
    delete this->sound;
    this->sound = nullptr;
}

Collectible& Collectible::operator=(const Collectible &original) {
    if (this != &original) {
        this->type = original.type;
        this->spawnArea = original.spawnArea;
        this->collected = original.collected;

        this->soundBuffer = new sf::SoundBuffer(*original.soundBuffer);
        this->sound = new sf::Sound(*original.sound);
        this->sound->setBuffer(*this->soundBuffer);
    }
    return *this;
}

Collectible* Collectible::clone() const {
    return new Collectible(*this);
}

Collectible::CollectibleType Collectible::getType() const {
    return this->type;
}

bool Collectible::isCollected() const {
    return this->collected;
}

void Collectible::setCollected() {
    this->collected = true;
    this->getAnimationHandler()->clearSequences();

    this->sound->play();
}

void Collectible::restore(const bool respawn) {
    if (!respawn) {
        this->collected = false;
        switch (this->type) {
            case CollectibleType::GoldCoin: {
                AnimationSequence *sequence = new AnimationSequence(this->getGame(), COIN_SEQUENCE_ID, "./resources/Misc.png");
                sequence->addFrame(sf::IntRect(70 * 8, 70 * 2, 70, 70), 10);
                this->getAnimationHandler()->addSequence(sequence);
                this->getAnimationHandler()->switchSequence(COIN_SEQUENCE_ID);
            } break;
            case CollectibleType::Life: {
                AnimationSequence *sequence = new AnimationSequence(this->getGame(), LIFE_SEQUENCE_ID, "./resources/Hud.png");
                sequence->addFrame(sf::IntRect(0, 48, 52, 48), 10);
                this->getAnimationHandler()->addSequence(sequence);
                this->getAnimationHandler()->switchSequence(LIFE_SEQUENCE_ID);
            } break;
        }
    }
}

void Collectible::processEvents() { }

void Collectible::update(const float dt) {
    sf::Vector2f velocity = this->getVelocity();
    sf::Vector2f position = this->getPosition();

    float minY, maxY;
    minY = (float)this->spawnArea.top;
    maxY = (float)(this->spawnArea.top + this->spawnArea.height - this->spawnArea.height / 1.5);

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
