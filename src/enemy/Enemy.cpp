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
#include "enemy/EnemySlimePurple.hpp"

#include <random>

const sf::Vector2f MAX_VELOCITY = {50, 100};

Enemy::Enemy(Game *game, const sf::IntRect spawnArea) : GameObject(game, true) {
    this->spawnArea = spawnArea;

    std::string rpath = "./resources/Enemy.wav";
    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->soundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);

    this->sound = new sf::Sound;
    this->sound->setBuffer(*this->soundBuffer);
}

Enemy::~Enemy() {
    delete this->sound;
    this->sound = nullptr;
}

void Enemy::handleMovement(const float dt) {
    auto rand = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine(std::random_device{}()));
    sf::Vector2f velocity = this->getVelocity();
    sf::Vector2f position = this->getPosition();
    if (this->alive) {
        if (this->spawnArea.width > this->spawnArea.height) {
            float minX = this->spawnArea.left + 65/2;
            float maxX = this->spawnArea.left + this->spawnArea.width - 65/2;
            if (velocity.x == 0) {
                velocity.x = (rand() % 2 == 0) ? 50 : -50;
                velocity.y = 0;
                position.x = minX + (rand() % (int)(maxX-minX));
                position.y = this->spawnArea.top + this->spawnArea.height - 65/2;
            }
            if (velocity.x < 0 && position.x < minX) {
                velocity.x = MAX_VELOCITY.x;
            }
            if (velocity.x > 0 && position.x > maxX) {
                velocity.x = -MAX_VELOCITY.x;
            }
            if (velocity.x < 0) {
                this->getAnimationHandler()->getCurrentSequence().getCurrentFrame().setScale({1, 1});
            } else {
                this->getAnimationHandler()->getCurrentSequence().getCurrentFrame().setScale({-1, 1});
            }
        } else {
            float minY = this->spawnArea.top + 65/2;
            float maxY = this->spawnArea.top + this->spawnArea.height - 65/2;
            if (velocity.y == 0) {
                velocity.x = 0;
                velocity.y = (rand() % 2 == 0) ? 50 : -50;
                position.x = this->spawnArea.left + 65/2;
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
    std::string animationIdentifier = this->alive ? "alive" : "dead";

    if (this->getAnimationHandler()->getCurrentSequence().getIdentifier() != animationIdentifier) {
        this->getAnimationHandler()->switchSequence(animationIdentifier);
    }

    this->getAnimationHandler()->getCurrentSequence().updateFrames(dt);
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
        this->configure();
    }
}

void Enemy::processEvents() {

}

void Enemy::update(const float dt) {
    this->handleMovement(dt);
    this->handleAnimation(dt);
}
