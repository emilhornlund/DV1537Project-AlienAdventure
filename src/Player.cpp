/**
 * @file Player.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <cmath>
#include <tic.h>

#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "Collectible.hpp"
#include "Enemy.hpp"
#include "EventHandler.hpp"
#include "Game.hpp"
#include "Hud.hpp"
#include "LevelHandler.hpp"
#include "ObjectHandler.hpp"
#include "Player.hpp"
#include "Renderer.hpp"
#include "ResourceHandler.hpp"
#include "World.hpp"

const std::string STATIONARY_LEFT_SEQUENCE_ID = "StationaryLeft";
const std::string STATIONARY_RIGHT_SEQUENCE_ID = "StationaryRight";
const std::string WALK_LEFT_SEQUENCE_ID = "WalkLeft";
const std::string WALK_RIGHT_SEQUENCE_ID = "WalkRight";
const std::string JUMP_LEFT_SEQUENCE_ID = "JumpLeft";
const std::string JUMP_RIGHT_SEQUENCE_ID = "JumpRight";
const std::string HURT_LEFT_SEQUENCE_ID = "HurtLeft";
const std::string HURT_RIGHT_SEQUENCE_ID = "HurtRight";

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

Player::Player(Game *game, const std::vector<sf::IntRect> &spawnAreas, const sf::IntRect exitArea) : GameObject(game) {
    this->setDepth(PLAYER_DEPTH);
    this->setBoundingBox({ 10, 10, 51, 89 });
    this->spawnAreas = spawnAreas;
    this->exitArea = exitArea;
    this->currentCharacter = 0;

    this->setupSounds();
}

Player::Player(const Player &original) : GameObject(original) {
    this->state = original.state;
    this->direction = original.direction;
    this->spawnAreas = original.spawnAreas;
    this->exitArea = original.exitArea;
    this->currentCharacter = original.currentCharacter;
    this->isHurt = original.isHurt;
    this->timeSinceHurt = original.timeSinceHurt;
    this->timeSinceGameOver = original.timeSinceGameOver;
    this->health = original.health;
    this->coins = original.coins;

    this->jumpSoundBuffer = new sf::SoundBuffer(*original.jumpSoundBuffer);
    this->jumpSound = new sf::Sound(*original.jumpSound);
    this->jumpSound->setBuffer(*this->jumpSoundBuffer);

    this->hurtSoundBuffer = new sf::SoundBuffer(*original.hurtSoundBuffer);
    this->hurtSound = new sf::Sound(*original.hurtSound);
    this->hurtSound->setBuffer(*this->hurtSoundBuffer);

    this->gameOverSoundBuffer = new sf::SoundBuffer(*original.gameOverSoundBuffer);
    this->gameOverSound = new sf::Sound(*original.gameOverSound);
    this->gameOverSound->setBuffer(*this->gameOverSoundBuffer);

    this->victoriousSoundBuffer = new sf::SoundBuffer(*original.victoriousSoundBuffer);
    this->victoriousSound = new sf::Sound(*original.victoriousSound);
    this->victoriousSound->setBuffer(*this->victoriousSoundBuffer);
}

Player::~Player() {
    delete this->jumpSound;
    this->jumpSound = nullptr;

    delete this->hurtSound;
    this->hurtSound = nullptr;

    delete this->gameOverSound;
    this->gameOverSound = nullptr;

    delete this->victoriousSound;
    this->victoriousSound = nullptr;
}

Player& Player::operator=(const Player &original) {
    if (this != &original) {
        this->state = original.state;
        this->direction = original.direction;
        this->spawnAreas = original.spawnAreas;
        this->exitArea = original.exitArea;
        this->isHurt = original.isHurt;
        this->timeSinceHurt = original.timeSinceHurt;
        this->timeSinceGameOver = original.timeSinceGameOver;
        this->health = original.health;
        this->coins = original.coins;

        this->jumpSoundBuffer = new sf::SoundBuffer(*original.jumpSoundBuffer);
        this->jumpSound = new sf::Sound(*original.jumpSound);
        this->jumpSound->setBuffer(*this->jumpSoundBuffer);

        this->hurtSoundBuffer = new sf::SoundBuffer(*original.hurtSoundBuffer);
        this->hurtSound = new sf::Sound(*original.hurtSound);
        this->hurtSound->setBuffer(*this->hurtSoundBuffer);

        this->gameOverSoundBuffer = new sf::SoundBuffer(*original.gameOverSoundBuffer);
        this->gameOverSound = new sf::Sound(*original.gameOverSound);
        this->gameOverSound->setBuffer(*this->gameOverSoundBuffer);

        this->victoriousSoundBuffer = new sf::SoundBuffer(*original.victoriousSoundBuffer);
        this->victoriousSound = new sf::Sound(*original.victoriousSound);
        this->victoriousSound->setBuffer(*this->victoriousSoundBuffer);
    }
    return *this;
}

Player* Player::clone() const {
    return new Player(*this);
}

void Player::setupSounds() {
    std::string rpath = "./resources/Jump.wav";
    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->jumpSoundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);
    this->jumpSound = new sf::Sound;
    this->jumpSound->setBuffer(*this->jumpSoundBuffer);
    this->jumpSound->setVolume(70);

    rpath = "./resources/Hurt.wav";
    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->hurtSoundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);
    this->hurtSound = new sf::Sound;
    this->hurtSound->setBuffer(*this->hurtSoundBuffer);
    this->hurtSound->setVolume(70);

    rpath = "./resources/GameOver.wav";
    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->gameOverSoundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);
    this->gameOverSound = new sf::Sound;
    this->gameOverSound->setBuffer(*this->gameOverSoundBuffer);
    this->gameOverSound->setVolume(70);

    rpath = "./resources/Victorious.wav";
    if (!this->getGame()->getSoundBufferResourceHandler()->isLoaded(rpath))
        this->getGame()->getSoundBufferResourceHandler()->load(rpath);
    this->victoriousSoundBuffer = &this->getGame()->getSoundBufferResourceHandler()->get(rpath);
    this->victoriousSound = new sf::Sound;
    this->victoriousSound->setBuffer(*this->victoriousSoundBuffer);
    this->victoriousSound->setVolume(40);
}

void Player::setupAnimations() const {
    this->getAnimationHandler()->clearSequences();

    std::string rpath = "./resources/Characters.png";

    int posY = this->currentCharacter * (int)PLAYER_SIZE.y;

    // Stationary left
    AnimationSequence *sequenceStationaryLeft = new AnimationSequence(this->getGame(), STATIONARY_LEFT_SEQUENCE_ID, rpath);
    sequenceStationaryLeft->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 1, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1, {-1, 1});
    sequenceStationaryLeft->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 0, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1);
    getAnimationHandler()->addSequence(sequenceStationaryLeft);

    // Stationary right
    AnimationSequence *sequenceStationaryRight = new AnimationSequence(this->getGame(), STATIONARY_RIGHT_SEQUENCE_ID, rpath);
    sequenceStationaryRight->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 1, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1);
    sequenceStationaryRight->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 0, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1);
    getAnimationHandler()->addSequence(sequenceStationaryRight);

    // Walk Left
    AnimationSequence *sequenceWalkLeft = new AnimationSequence(this->getGame(), WALK_LEFT_SEQUENCE_ID, rpath);
    sequenceWalkLeft->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 5, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 0.3, {-1, 1});
    sequenceWalkLeft->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 6, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 0.3, {-1, 1});
    getAnimationHandler()->addSequence(sequenceWalkLeft);

    // Walk Right
    AnimationSequence *sequenceWalkRight = new AnimationSequence(this->getGame(), WALK_RIGHT_SEQUENCE_ID, rpath);
    sequenceWalkRight->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 5, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 0.3);
    sequenceWalkRight->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 6, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 0.3);
    getAnimationHandler()->addSequence(sequenceWalkRight);

    // Jump Left
    AnimationSequence *sequenceJumpLeft = new AnimationSequence(this->getGame(), JUMP_LEFT_SEQUENCE_ID, rpath);
    sequenceJumpLeft->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 2, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1, {-1, 1});
    getAnimationHandler()->addSequence(sequenceJumpLeft);

    // Jump Right
    AnimationSequence *sequenceJumpRight = new AnimationSequence(this->getGame(), JUMP_RIGHT_SEQUENCE_ID, rpath);
    sequenceJumpRight->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 2, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1);
    getAnimationHandler()->addSequence(sequenceJumpRight);

    // Hurt Left
    AnimationSequence *sequenceHurtLeft = new AnimationSequence(this->getGame(), HURT_LEFT_SEQUENCE_ID, rpath);
    sequenceHurtLeft->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 4, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1, {-1, 1});
    getAnimationHandler()->addSequence(sequenceHurtLeft);

    // Hurt Right
    AnimationSequence *sequenceHurtRight = new AnimationSequence(this->getGame(), HURT_RIGHT_SEQUENCE_ID, rpath);
    sequenceHurtRight->addFrame(sf::IntRect((int)PLAYER_SIZE.x * 4, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y), 1);
    getAnimationHandler()->addSequence(sequenceHurtRight);
}

bool Player::isAlive() const {
    bool alive = true;
    if (this->getPosition().x < 0) {
        alive = false;
    }
    else if (this->getPosition().y < 0) {
        alive = false;
    }
    else if (this->getPosition().y > this->getGame()->getLevelHandler()->getWorldSize().y) {
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

void Player::bounceAgainstSide(const sf::Vector2f threshold, const sf::Vector2f distance) {
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
    for (unsigned int i = 0; i < this->getGame()->getObjectHandler()->getNumberOfObjects(); i++) {
        GameObject* objectPtr = this->getGame()->getObjectHandler()->getObject(i);

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
                                    this->getGame()->getHud()->setHealth(this->health);

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

        Enemy* enemyPtr = dynamic_cast<Enemy*>(objectPtr);
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
                    this->getGame()->getHud()->setHealth(this->health);

                    this->hurtSound->play();
                }
                this->setVelocity(velocity);
            }
        }

        Collectible* collectiblePtr = dynamic_cast<Collectible*>(objectPtr);
        if (collectiblePtr != nullptr) {
            sf::Vector2f threshold;
            threshold.x = 70/2 - 10 - (float)this->getBoundingBox().left + (float)this->getBoundingBox().width/2;
            threshold.y = 70/2 - 10 + (float)(this->getBoundingBox().top + this->getBoundingBox().height)/2;

            sf::Vector2f distance;
            distance.x = std::abs(collectiblePtr->getPosition().x - this->getPosition().x);
            distance.y = std::abs(collectiblePtr->getPosition().y - this->getPosition().y);

            if (std::abs(distance.x) < threshold.x && distance.y < threshold.y && !collectiblePtr->isCollected()) {
                switch (collectiblePtr->getType()) {
                    case Collectible::CollectibleType::GoldCoin: {
                        this->coins += 1;
                        this->getGame()->getHud()->setCoins(this->coins);
                    } break;
                    case Collectible::CollectibleType::Life: {
                        this->health += 1;
                        this->getGame()->getHud()->setHealth(this->health);
                    } break;
                }
                collectiblePtr->setCollected();
            }
        }
    }
}

void Player::handleAnimation(const float dt) {
    std::string animationIdentifier;
    switch (this->state) {
        case PlayerState::Stationary: {
            if (this->getVelocity().x == 0) {
                animationIdentifier = this->direction == PlayerDirection::Left ? STATIONARY_LEFT_SEQUENCE_ID : STATIONARY_RIGHT_SEQUENCE_ID;
            } else {
                animationIdentifier = this->direction == PlayerDirection::Left ? WALK_LEFT_SEQUENCE_ID : WALK_RIGHT_SEQUENCE_ID;
            }
        } break;
        case PlayerState::Walking: {
            animationIdentifier = this->direction == PlayerDirection::Left ? WALK_LEFT_SEQUENCE_ID : WALK_RIGHT_SEQUENCE_ID;
        } break;
        case PlayerState::Jumping: {
            if (this->isHurt) {
                animationIdentifier = this->direction == PlayerDirection::Left ? HURT_LEFT_SEQUENCE_ID : HURT_RIGHT_SEQUENCE_ID;
            } else {
                animationIdentifier = this->direction == PlayerDirection::Left ? JUMP_LEFT_SEQUENCE_ID : JUMP_RIGHT_SEQUENCE_ID;
            }
        } break;
        case PlayerState::Falling: {
            if (this->isHurt) {
                animationIdentifier = this->direction == PlayerDirection::Left ? HURT_LEFT_SEQUENCE_ID : HURT_RIGHT_SEQUENCE_ID;
            } else {
                animationIdentifier = this->direction == PlayerDirection::Left ? JUMP_LEFT_SEQUENCE_ID : JUMP_RIGHT_SEQUENCE_ID;
            }
        } break;
    }

    if (this->getAnimationHandler()->getCurrentSequence()->getIdentifier() != animationIdentifier) {
        this->getAnimationHandler()->switchSequence(animationIdentifier);
    }

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

    this->getAnimationHandler()->getCurrentSequence()->updateFrames(dt, flash);
}

void Player::updateCameraAndBackground() {
    this->getGame()->getRenderer()->updateCamera(this->getPosition());
}

void Player::restore(const bool respawn) {
    if (!respawn) {
        this->currentCharacter = (rand() % 5);
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
    this->getGame()->getHud()->setHealth(this->health);

    if (!respawn) {
        this->coins = 0;
        this->getGame()->getHud()->setCoins(this->coins);
    }
}

void Player::processEvents() {
    if (!this->isVictorious() && this->isAlive()) {
        bool leftPressed = this->getGame()->getEventHandler()->getKeyStatus(sf::Keyboard::Key::Left).down;
        bool rightPressed = this->getGame()->getEventHandler()->getKeyStatus(sf::Keyboard::Key::Right).down;
        bool spacePressed = this->getGame()->getEventHandler()->getKeyStatus(sf::Keyboard::Key::Space).pressed;
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

    if (this->getGame()->getState() == Game::GameState::Playing) {
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
                this->getGame()->setState(Game::GameState::GameOver);
            }
        }
        else if (!this->isAlive() && !this->isVictorious()) {
            if (this->timeSinceGameOver == 0) {
                this->getGame()->getHud()->setHealth(0);
                this->gameOverSound->play();
            }
            this->timeSinceGameOver += dt;
            if (this->timeSinceGameOver >= 1) {
                this->getGame()->setState(Game::GameState::Respawn);
            }
        }
    }

    this->updateCameraAndBackground();
}
