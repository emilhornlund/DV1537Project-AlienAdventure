/**
 * @file Enemy.cpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#include "Enemy.hpp"
#include "Game.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "AnimationFrame.hpp"
#include "ResourceHandler.hpp"

#include <iostream>

const std::string ALIVE_SEQUENCE_ID = "Alive";
const std::string DEAD_SEQUENCE_ID = "Dead";

const sf::Vector2f spriteSize = {65, 65};

const sf::Vector2f MAX_VELOCITY = {50, 100};

Enemy::Enemy(Game *game, const sf::IntRect spawnArea, const EnemyType enemyType) : GameObject(game) {
    this->spawnArea = spawnArea;
    this->type = enemyType;

    std::string rpath = "./resources/Enemy.wav";
    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->soundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);

    this->sound = new sf::Sound;
    this->sound->setBuffer(*this->soundBuffer);
}

Enemy::Enemy(const Enemy &original) : GameObject(original) {
    this->type = original.type;
    this->spawnArea = original.spawnArea;
    this->alive = original.alive;

    this->soundBuffer = new sf::SoundBuffer(*original.soundBuffer);
    this->sound = new sf::Sound(*original.sound);
    this->sound->setBuffer(*this->soundBuffer);
}

Enemy::~Enemy() {
    delete this->sound;
    this->sound = nullptr;
}

Enemy& Enemy::operator=(const Enemy &original) {
    if (this != &original) {
        this->type = original.type;
        this->spawnArea = original.spawnArea;
        this->alive = original.alive;

        this->soundBuffer = new sf::SoundBuffer(*original.soundBuffer);
        this->sound = new sf::Sound(*original.sound);
        this->sound->setBuffer(*this->soundBuffer);
    }
    return *this;
}

Enemy* Enemy::clone() const {
    return new Enemy(*this);
}

void Enemy::setupInitialPositionAndBoundingBoxes() {
    switch (this->type) {
        case EnemyType::SlimePurple: {
            this->setBoundingBox({8, 31, 49, 34});
        } break;
        case EnemyType::SlimeGreen: {
            this->setBoundingBox({8, 31, 49, 34});
        } break;
        case EnemyType::SlimeBlue: {
            this->setBoundingBox({8, 31, 49, 34});
        } break;
        case EnemyType::FishGreen: {
            this->setBoundingBox({4, 21, 57, 44});
        } break;
        case EnemyType::FishPink: {
            this->setBoundingBox({4, 21, 57, 44});
        } break;
        case EnemyType::FishBlue: {
            this->setBoundingBox({5, 5, 55, 60});
        } break;
        case EnemyType::Bee: {
            this->setBoundingBox({5, 21, 55, 48});
        } break;
        case EnemyType::BeeBlack: {
            this->setBoundingBox({5, 21, 55, 48});
        } break;
        case EnemyType::Snail: {
            this->setBoundingBox({3, 25, 59, 40});
        } break;
        case EnemyType::SnailMushroom: {
            this->setBoundingBox({3, 25, 59, 40});
        } break;
        case EnemyType::Mouse: {
            this->setBoundingBox({4, 31, 57, 34});
        } break;
        case EnemyType::Frog: {
            this->setBoundingBox({3, 13, 59, 52});
        } break;
        case EnemyType::WormGreen: {
            this->setBoundingBox({4, 43, 57, 22});
        } break;
        case EnemyType::WormPink: {
            this->setBoundingBox({4, 43, 57, 22});
        } break;
    }
}

void Enemy::setupAnimation() {
    this->getAnimationHandler()->clearSequences();
    std::string rpath = "./resources/Enemies.png";
    switch (this->type) {
        case SlimePurple: {
            int posY = (int)spriteSize.y*(SlimePurple-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*3, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case SlimeGreen: {
            int posY = (int)spriteSize.y*(SlimeGreen-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*3, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case SlimeBlue: {
            int posY = (int)spriteSize.y*(SlimeBlue-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*3, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case Bee: {
            int posY = (int)spriteSize.y*(Bee-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case BeeBlack: {
            int posY = (int)spriteSize.y*(BeeBlack-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case Snail: {
            int posY = (int)spriteSize.y*(Snail-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case SnailMushroom: {
            int posY = (int)spriteSize.y*(SnailMushroom-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case WormGreen: {
            int posY = (int)spriteSize.y*(WormGreen-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case WormPink: {
            int posY = (int)spriteSize.y*(WormPink-1);
            AnimationSequence *sequence = new AnimationSequence(this->getGame(), ALIVE_SEQUENCE_ID, rpath);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*0, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            sequence->addFrame(sf::IntRect((int)spriteSize.x*1, posY, (int)spriteSize.x, (int)spriteSize.y), 0.3);
            this->getAnimationHandler()->addSequence(sequence);

            AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), DEAD_SEQUENCE_ID, rpath);
            sequenceDead->addFrame(sf::IntRect((int)spriteSize.x*2, posY, (int)spriteSize.x, (int)spriteSize.y), 10);
            this->getAnimationHandler()->addSequence(sequenceDead);
        } break;
        case FishGreen:break;
        case FishPink:break;
        case FishBlue:break;
        case Mouse:break;
        case Frog:break;
    }
}

void Enemy::handleMovement(const float dt) {
    sf::Vector2f velocity = this->getVelocity();
    sf::Vector2f position = this->getPosition();
    if (this->alive) {
        if (this->spawnArea.width > this->spawnArea.height) {
            float minX = this->spawnArea.left + spriteSize.x/2;
            float maxX = this->spawnArea.left + this->spawnArea.width - spriteSize.x/2;
            if (velocity.x == 0) {
                velocity.x = (rand() % 2 == 0) ? 50 : -50;
                velocity.y = 0;
                position.x = minX + (rand() % (int)(maxX-minX));
                position.y = this->spawnArea.top + this->spawnArea.height - spriteSize.y/2;
            }
            if (velocity.x < 0 && position.x < minX) {
                velocity.x = MAX_VELOCITY.x;
            }
            if (velocity.x > 0 && position.x > maxX) {
                velocity.x = -MAX_VELOCITY.x;
            }
            if (velocity.x < 0) {
                this->getAnimationHandler()->getCurrentSequence()->getCurrentFrame()->setScale({1, 1});
            } else {
                this->getAnimationHandler()->getCurrentSequence()->getCurrentFrame()->setScale({-1, 1});
            }
        } else {
            float minY = this->spawnArea.top + spriteSize.y/2;
            float maxY = this->spawnArea.top + this->spawnArea.height - spriteSize.y/2;
            if (velocity.y == 0) {
                velocity.x = 0;
                velocity.y = (rand() % 2 == 0) ? 50 : -50;
                position.x = this->spawnArea.left + spriteSize.x/2;
                position.y = minY + (rand() % (int)(maxY-minY));
            }
            if (velocity.y < 0 && position.y < minY) {
                velocity.y = MAX_VELOCITY.y;

            }
            if (velocity.y > 0 && position.y > maxY) {
                velocity.y = -MAX_VELOCITY.y;
            }
        }
    } else {
        velocity.y -= -1000 * dt;
    }
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    this->setVelocity(velocity);
    this->setPosition(position);
}

void Enemy::handleAnimation(const float dt) {
    std::string animationIdentifier = this->alive ? ALIVE_SEQUENCE_ID : DEAD_SEQUENCE_ID;

    if (this->getAnimationHandler()->getCurrentSequence()->getIdentifier() != animationIdentifier) {
        this->getAnimationHandler()->switchSequence(animationIdentifier);
    }

    this->getAnimationHandler()->getCurrentSequence()->updateFrames(dt);
}

bool Enemy::isAlive() {
    return this->alive;
}

void Enemy::setDead() {
    this->alive = false;

    this->setDepth(ENEMY_DEAD_DEPTH);

    sf::Vector2f velocity = this->getVelocity();
    velocity.y = -300;
    this->setVelocity(velocity);

    this->sound->play();
}

void Enemy::restore(const bool respawn) {
    if (!respawn) {
        this->setVelocity({0, 0});
        this->alive = true;
        this->setDepth(ENEMY_ALIVE_DEPTH);
        this->setupInitialPositionAndBoundingBoxes();
        this->setupAnimation();
    }
}

void Enemy::processEvents() { }

void Enemy::update(const float dt) {
    this->handleMovement(dt);
    this->handleAnimation(dt);
}
