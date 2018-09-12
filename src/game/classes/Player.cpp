/**
 * @file Player.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "core/classes/AnimatedEntity.hpp"
#include "core/classes/Animation.hpp"
#include "core/classes/Camera.hpp"
#include "core/classes/EventHandler.hpp"
#include "core/classes/ObjectHandler.hpp"
#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/WindowHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/CollectibleCoin.hpp"
#include "game/classes/CollectibleHealth.hpp"
#include "game/classes/Player.hpp"
#include "game/classes/World.hpp"
#include "game/interfaces/IEnemy.hpp"

#include <random>

#include <SFML/Graphics/Texture.hpp>

const sf::Vector2f GRAVITY = { 0, -1000 };
const sf::Vector2f MAX_ACCELERATION(400, 0);
const sf::Vector2f MAX_VELOCITY(300, 550);
const sf::Vector2f HURT_VELOCITY(200, 350);
const float ACCELERATE_BY = 1600;
const float VELOCITY_HURT_THRESHOLD = 800;

const float HURT_DURATION = 3;
const float HURT_FLASH_SPEED = 0.05;

const sf::Vector2f TILE_SIZE = {70, 70};
const sf::Vector2f PLAYER_SIZE = {71, 99};

const int SPAWN_DELAY = 1;

Player::Player(IGame *game, const std::vector<sf::IntRect> &spawnAreas, const sf::IntRect &exitArea) : IGameObject(game,
                                                                                                                   IGameObject::DRAW_ORDER_PLAYER,
                                                                                                                   true) {
    this->setBoundingBox({ 10, 10, 51, 89 });
    this->spawnAreas = spawnAreas;
    this->exitArea = exitArea;
    this->currentCharacter = 0;

    this->setupSounds();

    auto* entity = new AnimatedEntity(false);
    entity->setOrigin(PLAYER_SIZE.x/2, PLAYER_SIZE.y/2);
    this->addEntity(entity);
}

Player::~Player() = default;

void Player::setupSounds() {
    this->jumpSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("./resources/Jump.wav");
    this->jumpSound = std::make_shared<sf::Sound>();
    this->jumpSound->setBuffer(*this->jumpSoundBuffer);
    this->jumpSound->setVolume(70);

    this->hurtSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("./resources/Hurt.wav");
    this->hurtSound = std::make_shared<sf::Sound>();
    this->hurtSound->setBuffer(*this->hurtSoundBuffer);
    this->hurtSound->setVolume(70);

    this->gameOverSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("./resources/GameOver.wav");
    this->gameOverSound = std::make_shared<sf::Sound>();
    this->gameOverSound->setBuffer(*this->gameOverSoundBuffer);
    this->gameOverSound->setVolume(70);

    this->victoriousSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("./resources/Victorious.wav");
    this->victoriousSound = std::make_shared<sf::Sound>();
    this->victoriousSound->setBuffer(*this->victoriousSoundBuffer);
    this->victoriousSound->setVolume(40);
}

void Player::setupAnimations() {
    const auto& spritesheet = this->getGame()->getTextureResourceHandler().load("./resources/Characters.png");

    int posY = this->currentCharacter * (int)PLAYER_SIZE.y;

    this->m_stationaryLeftAnimation = std::make_shared<Animation>(sf::seconds(1.f));
    this->m_stationaryLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 1, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 0, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryLeftAnimation->setSpriteSheet(spritesheet);

    this->m_stationaryRightAnimation = std::make_shared<Animation>(sf::seconds(1.f));
    this->m_stationaryRightAnimation->addFrame({(int)PLAYER_SIZE.x * 1, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryRightAnimation->addFrame({(int)PLAYER_SIZE.x * 0, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryRightAnimation->setSpriteSheet(spritesheet);

    this->m_walkLeftAnimation = std::make_shared<Animation>();
    this->m_walkLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 5, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 6, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkLeftAnimation->setSpriteSheet(spritesheet);

    this->m_walkRightAnimation = std::make_shared<Animation>();
    this->m_walkRightAnimation->addFrame({(int)PLAYER_SIZE.x * 5, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkRightAnimation->addFrame({(int)PLAYER_SIZE.x * 6, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkRightAnimation->setSpriteSheet(spritesheet);

    this->m_jumpLeftAnimation = std::make_shared<Animation>();
    this->m_jumpLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 2, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_jumpLeftAnimation->setSpriteSheet(spritesheet);

    this->m_jumpRightAnimation = std::make_shared<Animation>();
    this->m_jumpRightAnimation->addFrame({(int)PLAYER_SIZE.x * 2, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_jumpRightAnimation->setSpriteSheet(spritesheet);

    this->m_hurtLeftAnimation = std::make_shared<Animation>();
    this->m_hurtLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 4, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_hurtLeftAnimation->setSpriteSheet(spritesheet);

    this->m_hurtRightAnimation = std::make_shared<Animation>();
    this->m_hurtRightAnimation->addFrame({(int)PLAYER_SIZE.x * 4, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_hurtRightAnimation->setSpriteSheet(spritesheet);
}

bool Player::isAlive() const {
    bool alive = true;
    if (this->getPosition().x < 0) {
        alive = false;
    }
    else if (this->getPosition().y < 0) {
        alive = false;
    }
    else if (this->getPosition().y > this->getGame()->getPropertyHandler().get<sf::Vector2i>("worldSize").y) {
        alive = false;
    }
    else if (this->health == 0) {
        alive = false;
    }
    return alive;
}

bool Player::isVictorious() const {
    bool victorious = false;
    if (this->getPosition().x > this->exitArea.left &&
        this->getPosition().y > this->exitArea.top &&
        this->getPosition().y < this->exitArea.top + this->exitArea.height) {
        victorious = true;
    }
    return victorious;
}

void Player::decelerate(const float dt) {
    sf::Vector2f acceleration = this->getAcceleration();
    sf::Vector2f velocity = this->getVelocity();
    if (velocity.x > 0) {
        velocity.x -= this->getAcceleration().x * 2 * dt;
        if (velocity.x < 0) {
            acceleration = {0, 0};
            velocity.x = 0;
        }
    }
    if (velocity.x < 0) {
        velocity.x += this->getAcceleration().x * 2 * dt;
        if (velocity.x > 0) {
            acceleration = {0, 0};
            velocity.x = 0;
        }
    }
    this->setAcceleration(acceleration);
    this->setVelocity(velocity);
}

void Player::accelerate(const float dt) {
    //öka accelerationen tills dess den når max
    sf::Vector2f acceleration = this->getAcceleration();
    acceleration.x += ACCELERATE_BY * dt;
    if (acceleration.x > MAX_ACCELERATION.x) {
        acceleration.x = MAX_ACCELERATION.x;
    }
    //öka hastigheten beroende på riktningen tills den når max
    sf::Vector2f velocity = this->getVelocity();
    switch (this->direction) {
        case PlayerDirection::Left:
            if (velocity.x > 0) {
                velocity.x -= this->getAcceleration().x * 2 * dt;
            } else {
                velocity.x -= acceleration.x * dt;
                if (velocity.x < -MAX_VELOCITY.x) {
                    velocity.x = -MAX_VELOCITY.x;
                }
            }
            break;
        case PlayerDirection::Right:
            if (velocity.x < 0) {
                velocity.x += this->getAcceleration().x * 2 * dt;
            } else {
                velocity.x += acceleration.x * dt;
                if (velocity.x > MAX_VELOCITY.x) {
                    velocity.x = MAX_VELOCITY.x;
                }
            }
            break;
    }
    this->setAcceleration(acceleration);
    this->setVelocity(velocity);
}

void Player::updatePosition(const float dt) {
    sf::Vector2f position = this->getPosition();
    position.x += this->getVelocity().x * dt;
    position.y += this->getVelocity().y * dt;
    this->setPosition(position);
}

void Player::applyGravity(const float dt) {
    sf::Vector2f velocity = this->getVelocity();
    velocity.y -= GRAVITY.y * dt;
    if (velocity.y > 0) {
        if (velocity.x > 0) {
            velocity.x -= 200 * dt;
            if (velocity.x < 0) {
                velocity.x = 0;
            }
        }
        if (velocity.x < 0) {
            velocity.x += 200 * dt;
            if (velocity.x > 0) {
                velocity.x = 0;
            }
        }
    }
    this->setVelocity(velocity);
}

void Player::bounceAgainstSide(const sf::Vector2f &threshold, const sf::Vector2f &distance) {
    sf::Vector2f velocity = this->getVelocity();
    velocity.x *= -1;
    velocity.x *= 0.5;
    this->setVelocity(velocity);

    float overlap = threshold.x - std::abs(distance.x) + this->getBoundingBox().left;
    if (distance.x > 0) overlap *= -1;

    this->move({overlap, 0});
}

void Player::handleMovement(const float dt) {
    switch (this->state) {
        case PlayerState::Stationary: {
            this->decelerate(dt);
            this->updatePosition(dt);
        } break;
        case PlayerState::Jumping: {
            sf::Vector2f velocity = this->getVelocity();
            if (velocity.y > 0) {
                this->state = PlayerState::Falling;
            } else {
                if ((velocity.x > 0 && this->direction == PlayerDirection::Left) || (velocity.x < 0 && this->direction == PlayerDirection::Right)) {
                    velocity.x = 0;
                }
                if (velocity.y == 0) {
                    velocity.y = -std::abs(MAX_VELOCITY.y);
                    this->setVelocity(velocity);
                    this->jumpSound->play();
                }
                this->updatePosition(dt);
                this->applyGravity(dt);
            }
        } break;
        case PlayerState::Falling: {
            this->updatePosition(dt);
            this->applyGravity(dt);
        } break;
        case PlayerState::Walking: {
            this->accelerate(dt);
            this->updatePosition(dt);
        } break;
    }
}

void Player::handleCollision() {
    for (unsigned int i = 0; i < this->getGame()->getObjectHandler().getNumberOfObjects(); i++) {
        auto *objectPtr = &this->getGame()->getObjectHandler().getObject(i);

        World* worldPtr = dynamic_cast<World*>(objectPtr);
        if (worldPtr != nullptr) {

            sf::Vector2f threshold;
            threshold.x = (float)worldPtr->getTileSize().y/2 - (float)this->getBoundingBox().left + (float)this->getBoundingBox().width/2;
            threshold.y = (float)worldPtr->getTileSize().y/2 + (float)(this->getBoundingBox().top + this->getBoundingBox().height)/2;

            sf::Vector2f distance = worldPtr->getShortestCollisionDistance(this->getPosition());

            if (std::abs(distance.x) < threshold.x && std::abs(distance.y) < threshold.y) {
                sf::Vector2f velocity = this->getVelocity();
                sf::Vector2f overlap = { threshold.x - std::abs(distance.x), threshold.y - std::abs(distance.y) };
                switch (this->state) {
                    case PlayerState::Stationary: {
                        if (distance.y == (PLAYER_SIZE.y-TILE_SIZE.y)/2) {
                            this->bounceAgainstSide(threshold, distance);
                        }
                    } break;
                    case PlayerState::Jumping: {
                        if (overlap.y < overlap.x) {
                            velocity.y = std::abs(velocity.y);
                            this->setVelocity(velocity);
                            this->move({0, overlap.y});
                        } else {
                            this->bounceAgainstSide(threshold, distance);
                        }
                    } break;
                    case PlayerState::Falling: {
                        if (overlap.y < overlap.x) {
                            if (distance.y > 0) {
                                if (velocity.y >= VELOCITY_HURT_THRESHOLD && !this->initialFall && !this->isHurt) {
                                    this->state = PlayerState::Jumping;
                                    this->isHurt = true;

                                    this->move({0, -overlap.y});
                                    velocity.y = -HURT_VELOCITY.y;
                                    this->setVelocity(velocity);

                                    this->health -= 1;
                                    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->health);

                                    this->hurtSound->play();
                                } else {
                                    if (this->initialFall)
                                        this->initialFall = false;

                                    this->move({0, -overlap.y});
                                    velocity.y = 0;
                                    this->setVelocity(velocity);
                                    this->state = PlayerState::Stationary;
                                }
                            } else {
                                this->move({0, overlap.y});
                                velocity.y = std::abs(velocity.y);
                                this->setVelocity(velocity);
                            }
                        } else {
                            this->bounceAgainstSide(threshold, distance);
                        }
                    } break;
                    case PlayerState::Walking: {
                        if (distance.y == (PLAYER_SIZE.y-TILE_SIZE.y)/2) {
                            this->bounceAgainstSide(threshold, distance);
                            if (std::abs(velocity.x) > 150) {
                                velocity.y = -std::abs(velocity.x)/2;
                                this->setVelocity(velocity);
                                this->state = PlayerState::Jumping;
                            }
                        }
                    } break;
                }
            } else if (std::abs(distance.x) > threshold.x && distance.y > (PLAYER_SIZE.y-TILE_SIZE.y)/2) {
                this->state = PlayerState::Falling;
            }
        }

        IEnemy* enemyPtr = dynamic_cast<IEnemy*>(objectPtr);
        if (enemyPtr != nullptr && enemyPtr->isAlive()) {
            float ax = this->getBoundingBox().width/2 + this->getBoundingBox().left;
            float bx = enemyPtr->getBoundingBox().width/2 + enemyPtr->getBoundingBox().left;

            sf::Vector2f diff;
            diff.x = std::abs(enemyPtr->getPosition().x - this->getPosition().x);

            float aPosY = this->getPosition().y + this->getBoundingBox().top/2;
            float bPosY = enemyPtr->getPosition().y + enemyPtr->getBoundingBox().top/2;
            diff.y = std::abs(aPosY - bPosY);

            if (diff.x < ax + bx) {
                sf::Vector2f velocity = this->getVelocity();
                if (this->getPosition().y < enemyPtr->getPosition().y && (diff.y < (this->getBoundingBox().height/2 + enemyPtr->getBoundingBox().top)) && (diff.y > (this->getBoundingBox().height/2 + enemyPtr->getBoundingBox().top)*0.9) && this->state == PlayerState::Falling) {
                    enemyPtr->setDead();
                    velocity.y = -(MAX_VELOCITY.y/2);
                }
                else if (((diff.y < this->getBoundingBox().height/2 + enemyPtr->getBoundingBox().top) ||
                          (diff.y < enemyPtr->getBoundingBox().height/2 + this->getBoundingBox().top)) && !this->isHurt) {
                    this->state = PlayerState::Jumping;
                    this->isHurt = true;

                    velocity.x *= -1;
                    velocity.x *= 0.5;
                    velocity.y = -HURT_VELOCITY.y;

                    this->health -= 1;
                    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->health);

                    this->hurtSound->play();
                }
                this->setVelocity(velocity);
            }
        }

        ICollectible* collectiblePtr = dynamic_cast<ICollectible*>(objectPtr);
        if (collectiblePtr != nullptr) {
            sf::Vector2f threshold;
            threshold.x = 70/2 - 10 - (float)this->getBoundingBox().left + (float)this->getBoundingBox().width/2;
            threshold.y = 70/2 - 10 + (float)(this->getBoundingBox().top + this->getBoundingBox().height)/2;

            sf::Vector2f distance;
            distance.x = std::abs(collectiblePtr->getPosition().x - this->getPosition().x);
            distance.y = std::abs(collectiblePtr->getPosition().y - this->getPosition().y);

            if (std::abs(distance.x) < threshold.x && distance.y < threshold.y && !collectiblePtr->isCollected()) {
                auto *coin = dynamic_cast<CollectibleCoin*>(collectiblePtr);
                if (coin != nullptr) {
                    this->coins += 1;
                    this->getGame()->getPropertyHandler().set<unsigned int>("coins", this->coins);
                }
                auto *healthPtr = dynamic_cast<CollectibleHealth*>(collectiblePtr);
                if (healthPtr != nullptr) {
                    this->health += 1;
                    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->health);
                }
                collectiblePtr->setCollected(true);
            }
        }
    }
}

void Player::handleAnimation(const float dt) {

    auto* entity = &this->getEntity(0);
    auto* animatedEntity = dynamic_cast<AnimatedEntity*>(entity);
    if (animatedEntity == nullptr)
        return;

    const Animation* nextAnimation = nullptr;
    switch (this->state) {
        case PlayerState::Stationary: {
            if (this->getVelocity().x == 0) {
                nextAnimation = this->direction == PlayerDirection::Left ? this->m_stationaryLeftAnimation.get() : this->m_stationaryRightAnimation.get();
            } else {
                nextAnimation = this->direction == PlayerDirection::Left ? this->m_walkLeftAnimation.get() : this->m_walkRightAnimation.get();
            }
        } break;
        case PlayerState::Walking: {
            nextAnimation = this->direction == PlayerDirection::Left ? this->m_walkLeftAnimation.get() : this->m_walkRightAnimation.get();
        } break;
        case PlayerState::Jumping: {
            if (this->isHurt) {
                nextAnimation = this->direction == PlayerDirection::Left ? this->m_hurtLeftAnimation.get() : this->m_hurtRightAnimation.get();
            } else {
                nextAnimation = this->direction == PlayerDirection::Left ? this->m_jumpLeftAnimation.get() : this->m_jumpRightAnimation.get();
            }
        } break;
        case PlayerState::Falling: {
            if (this->isHurt) {
                nextAnimation = this->direction == PlayerDirection::Left ? this->m_hurtLeftAnimation.get() : this->m_hurtRightAnimation.get();
            } else {
                nextAnimation = this->direction == PlayerDirection::Left ? this->m_jumpLeftAnimation.get() : this->m_jumpRightAnimation.get();
            }
        } break;
    }

    if (nextAnimation != animatedEntity->getAnimation()) {
        animatedEntity->play(*nextAnimation);
        switch (this->direction) {
            case PlayerDirection::Left:
                animatedEntity->setScale({-1, 1});
                break;
            case PlayerDirection::Right:
                animatedEntity->setScale({1, 1});
                break;
        }
    }
    animatedEntity->update(sf::seconds(dt));

    sf::Color flash;
    if (this->isHurt) {
        int currentFlash = (int)(this->timeSinceHurt / HURT_FLASH_SPEED) + 1;
        if (currentFlash % 2 == 1) {
            flash = sf::Color(255, 255, 255, 128);
        } else {
            flash = sf::Color(255, 255, 255, 230);
        }
    } else {
        flash = sf::Color(255, 255, 255, 255);
    }
    animatedEntity->setColor(flash);
}

void Player::updateCameraAndBackground() {
    this->getGame()->getWindowHandler().getCamera().setCenter(this->getPosition());
}

void Player::restore(const bool respawn) {
    if (!respawn) {
        auto rand = std::bind(std::uniform_int_distribution<>(0,5),std::default_random_engine(std::random_device{}()));
        this->currentCharacter = rand() % 5;
    }
    this->setupAnimations();

    this->setAcceleration({0, 0});
    this->setVelocity({0, 1});

    int spawnIndex = 0;
    for (int i = 0; i < this->spawnAreas.size() && respawn; i++) {
        if (this->getPosition().x >= this->spawnAreas[i].left) {
            spawnIndex = i;
        }
    }
    sf::Vector2f position;
    position.x = (float)spawnAreas[spawnIndex].left+this->getBoundingBox().width/2;
    position.y = 0;
    this->setPosition(position);

    this->setVisible(false);

    this->state = PlayerState::Falling;
    this->direction = PlayerDirection::Right;
    this->isHurt = false;
    this->initialFall = true;

    this->timeSinceNewGame = 0;
    this->timeSinceGameOver = 0;
    this->timeSinceHurt = 0;

    this->health = 3;
    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->health);

    if (!respawn) {
        this->coins = 0;
        this->getGame()->getPropertyHandler().set<unsigned int>("coins", this->coins);
    }
}

void Player::processEvents() {
    if (!this->isVictorious() && this->isAlive()) {
        bool leftPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Left).down;
        bool rightPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Right).down;
        bool spacePressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Space).pressed;
        switch (this->state) {
            case PlayerState::Stationary:
                if (leftPressed != rightPressed) {
                    this->state = PlayerState::Walking;
                    if (leftPressed) {
                        this->direction = PlayerDirection::Left;
                    }
                    if (rightPressed) {
                        this->direction = PlayerDirection::Right;
                    }
                } else if (spacePressed) {
                    this->state = PlayerState::Jumping;
                }
                break;
            case PlayerState::Walking:
                if (leftPressed != rightPressed) {
                    if (leftPressed) {
                        this->direction = PlayerDirection::Left;
                    }
                    if (rightPressed) {
                        this->direction = PlayerDirection::Right;
                    }
                }
                if (leftPressed == rightPressed) {
                    this->state = PlayerState::Stationary;
                }
                if (spacePressed) {
                    this->state = PlayerState::Jumping;
                }
                break;
            default:
                break;
        }
    }
}

void Player::update(const float dt) {
    if (this->isVisible()) {
        this->handleMovement(dt);
        this->handleAnimation(dt);
    }

    if (this->isHurt) {
        this->timeSinceHurt += dt;
        if (this->timeSinceHurt >= HURT_DURATION) {
            this->timeSinceHurt = 0;
            this->isHurt = false;
        }
    }

    if (this->timeSinceNewGame >= SPAWN_DELAY) {
        if (this->timeSinceNewGame != 0) {
            this->timeSinceNewGame = 0;
            this->setVisible(true);
        }
    } else if (!this->isVisible()) {
        this->timeSinceNewGame += dt;
    }
    if (this->isVisible() && this->isAlive()) {
        this->handleCollision();
    }

    if (this->getGame()->getState() == IGame::GameState::Playing) {
        if (this->isVictorious() && this->isAlive()) {
            if (this->getVelocity().y == 0) {
                this->state = PlayerState::Walking;
                this->direction = PlayerDirection::Right;
            }
            if (this->timeSinceGameOver == 0) {
                this->victoriousSound->play();
            }
            this->timeSinceGameOver += dt;
            if (this->timeSinceGameOver >= 0.5) {
                this->getGame()->setState(IGame::GameState::GameOver);
            }
        }
        else if (!this->isAlive() && !this->isVictorious()) {
            if (this->timeSinceGameOver == 0) {
                this->getGame()->getPropertyHandler().set<unsigned int>("health", 0);
                this->gameOverSound->play();
            }
            this->timeSinceGameOver += dt;
            if (this->timeSinceGameOver >= 1) {
                this->getGame()->setState(IGame::GameState::Respawn);
            }
        }
    }

    this->updateCameraAndBackground();
}
