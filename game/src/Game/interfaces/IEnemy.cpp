/**
 * @file Enemy.cpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#include "../../../lib/include/classes/AnimatedEntity.hpp"
#include "../../../lib/include/classes/ResourceHandler.hpp"
#include "../../../lib/include/interfaces/IGame.hpp"
#include "../../include/classes/EnemySlimePurple.hpp"
#include "../../include/classes/Game.hpp"
#include "../../include/classes/GameScene.hpp"
#include "../../include/interfaces/IEnemy.hpp"

#include <random>
#include <functional>

const sf::Vector2f MAX_VELOCITY = {50, 100};

IEnemy::IEnemy(IGame *game, const sf::IntRect &spawnArea) : IGameObject(game, GameScene::DRAW_ORDER_ENEMY_ALIVE, true) {
    this->m_spawnArea = spawnArea;
    this->m_direction = EnemyDirection::None;

    this->m_soundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("Enemy.wav");

    this->m_sound = new sf::Sound;
    this->m_sound->setBuffer(*this->m_soundBuffer);

    auto entity = std::make_shared<AnimatedEntity>();
    entity->setOrigin((float)65/2, (float)65/2);
    this->addEntity(entity);
}

IEnemy::~IEnemy() {
    delete this->m_sound;
    this->m_sound = nullptr;
}

const IEnemy::EnemyDirection &IEnemy::getDirection() const {
    return this->m_direction;
}

void IEnemy::handleMovement(const float dt) {
    auto rand = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine(std::random_device{}()));
    sf::Vector2f velocity = this->getVelocity();
    sf::Vector2f position = this->getPosition();
    if (this->m_alive) {
        if (this->m_spawnArea.width > this->m_spawnArea.height) {
            float minX = this->m_spawnArea.left + 65/2;
            float maxX = this->m_spawnArea.left + this->m_spawnArea.width - 65/2;
            if (velocity.x == 0) {
                velocity.x = (rand() % 2 == 0) ? 50 : -50;
                velocity.y = 0;
                position.x = minX + (rand() % (int)(maxX-minX));
                position.y = this->m_spawnArea.top + this->m_spawnArea.height - 65/2;
            }
            if (velocity.x < 0 && position.x < minX) {
                velocity.x = MAX_VELOCITY.x;
            }
            if (velocity.x > 0 && position.x > maxX) {
                velocity.x = -MAX_VELOCITY.x;
            }
            if (velocity.x < 0) {
                if (this->m_direction == EnemyDirection::None || this->m_direction == EnemyDirection::Left) {
                    this->m_direction = EnemyDirection::Right;
                }
            } else {
                if (this->m_direction == EnemyDirection::None || this->m_direction == EnemyDirection::Right) {
                    this->m_direction = EnemyDirection::Left;
                }
            }
        } else {
            float minY = this->m_spawnArea.top + 65/2;
            float maxY = this->m_spawnArea.top + this->m_spawnArea.height - 65/2;
            if (velocity.y == 0) {
                velocity.x = 0;
                velocity.y = (rand() % 2 == 0) ? 50 : -50;
                position.x = this->m_spawnArea.left + 65/2;
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

void IEnemy::handleAnimation(const float dt) {
    auto* animatedEntity = dynamic_cast<AnimatedEntity*>(&this->getEntity(0));
    if (animatedEntity != nullptr) {
        if (this->isAlive() && animatedEntity->getAnimation() != &this->getMovingAnimation()) {
            animatedEntity->play(this->getMovingAnimation());
        } else if (!this->isAlive() && animatedEntity->getAnimation() != &this->getDeadAnimation()) {
            animatedEntity->play(this->getDeadAnimation());
        }
        switch (this->getDirection()) {
            case EnemyDirection::None:
            case EnemyDirection::Right:
                animatedEntity->setScale({1, 1});
                break;
            case EnemyDirection::Left:
                animatedEntity->setScale({-1, 1});
                break;
        }
        animatedEntity->update(sf::seconds(dt));
    }
}

bool IEnemy::isAlive() {
    return this->m_alive;
}

void IEnemy::setDead() {
    this->m_alive = false;

    this->setZIndex(GameScene::DRAW_ORDER_ENEMY_DEAD);

    sf::Vector2f velocity = this->getVelocity();
    velocity.y = -300;
    this->setVelocity(velocity);

    this->m_sound->play();
}

void IEnemy::restore(const bool respawn) {
    if (!respawn) {
        if (!this->m_alive) {
            this->setVelocity({0, 0});
        }
        this->m_alive = true;
        this->setZIndex(GameScene::DRAW_ORDER_ENEMY_ALIVE);
    }
}

void IEnemy::processEvents() {

}

void IEnemy::update(const float dt) {
    this->handleMovement(dt);
    this->handleAnimation(dt);
}
