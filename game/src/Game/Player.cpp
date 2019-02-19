/**
 * @file Player.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Core/AnimatedEntity.hpp>
#include <Core/Animation.hpp>
#include <Core/Camera.hpp>
#include <Core/EventHandler.hpp>
#include <Core/ObjectHandler.hpp>
#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SceneHandler.hpp>
#include <Core/WindowHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IScene.hpp>

#include <Game/CollectibleCoin.hpp>
#include <Game/CollectibleHealth.hpp>
#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/Player.hpp>
#include <Game/World.hpp>
#include <Game/IEnemy.hpp>

#include <SFML/Graphics/Texture.hpp>

#include <random>
#include <functional>

const sf::Vector2f GRAVITY = { 0, -1000 };
const sf::Vector2f MAX_ACCELERATION(400, 0);
const sf::Vector2f MAX_VELOCITY(300, 550);
const sf::Vector2f HURT_VELOCITY(200, 350);
const float ACCELERATE_BY = 1600;
const float VELOCITY_HURT_THRESHOLD = 800;

const float HURT_DURATION = 3;
const float HURT_FLASH_SPEED = 0.1;

const sf::Vector2f TILE_SIZE = {70, 70};
const sf::Vector2f PLAYER_SIZE = {71, 99};

const int SPAWN_DELAY = 1;

AA::Player::Player(CGL::IGame *game, const std::vector<sf::IntRect> &spawnAreas, const sf::IntRect &exitArea) : IGameObject(game, GameScene::DRAW_ORDER_PLAYER, true),
                                                                                                             m_isJumping(false),
                                                                                                             m_wasJumping(false) {
    this->setBoundingBox({ 10, 10, 51, 89 });
    this->m_spawnAreas = spawnAreas;
    this->m_exitArea = exitArea;
    this->m_currentCharacter = 0;

    this->setupSounds();

    auto entity = std::make_shared<CGL::AnimatedEntity>();
    entity->setOrigin(PLAYER_SIZE.x/2, PLAYER_SIZE.y/2);
    this->addEntity(entity);
}

AA::Player::~Player() = default;

void AA::Player::setupSounds() {
    this->m_jumpSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("Jump.wav");
    this->m_jumpSound = std::make_shared<sf::Sound>();
    this->m_jumpSound->setBuffer(*this->m_jumpSoundBuffer);
    this->m_jumpSound->setVolume(70);

    this->m_hurtSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("Hurt.wav");
    this->m_hurtSound = std::make_shared<sf::Sound>();
    this->m_hurtSound->setBuffer(*this->m_hurtSoundBuffer);
    this->m_hurtSound->setVolume(70);

    this->m_gameOverSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("GameOver.wav");
    this->m_gameOverSound = std::make_shared<sf::Sound>();
    this->m_gameOverSound->setBuffer(*this->m_gameOverSoundBuffer);
    this->m_gameOverSound->setVolume(70);

    this->m_victoriousSoundBuffer = &this->getGame()->getSoundBufferResourceHandler().load("Victorious.wav");
    this->m_victoriousSound = std::make_shared<sf::Sound>();
    this->m_victoriousSound->setBuffer(*this->m_victoriousSoundBuffer);
    this->m_victoriousSound->setVolume(40);
}

void AA::Player::setupAnimations() {
    const auto& spritesheet = this->getGame()->getTextureResourceHandler().load("Characters.png");

    int posY = this->m_currentCharacter * (int)PLAYER_SIZE.y;

    this->m_stationaryLeftAnimation = std::make_shared<CGL::Animation>(sf::seconds(1.f));
    this->m_stationaryLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 1, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 0, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryLeftAnimation->setSpriteSheet(spritesheet);

    this->m_stationaryRightAnimation = std::make_shared<CGL::Animation>(sf::seconds(1.f));
    this->m_stationaryRightAnimation->addFrame({(int)PLAYER_SIZE.x * 1, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryRightAnimation->addFrame({(int)PLAYER_SIZE.x * 0, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_stationaryRightAnimation->setSpriteSheet(spritesheet);

    this->m_walkLeftAnimation = std::make_shared<CGL::Animation>();
    this->m_walkLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 5, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 6, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkLeftAnimation->setSpriteSheet(spritesheet);

    this->m_walkRightAnimation = std::make_shared<CGL::Animation>();
    this->m_walkRightAnimation->addFrame({(int)PLAYER_SIZE.x * 5, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkRightAnimation->addFrame({(int)PLAYER_SIZE.x * 6, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_walkRightAnimation->setSpriteSheet(spritesheet);

    this->m_jumpLeftAnimation = std::make_shared<CGL::Animation>();
    this->m_jumpLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 2, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_jumpLeftAnimation->setSpriteSheet(spritesheet);

    this->m_jumpRightAnimation = std::make_shared<CGL::Animation>();
    this->m_jumpRightAnimation->addFrame({(int)PLAYER_SIZE.x * 2, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_jumpRightAnimation->setSpriteSheet(spritesheet);

    this->m_hurtLeftAnimation = std::make_shared<CGL::Animation>();
    this->m_hurtLeftAnimation->addFrame({(int)PLAYER_SIZE.x * 4, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_hurtLeftAnimation->setSpriteSheet(spritesheet);

    this->m_hurtRightAnimation = std::make_shared<CGL::Animation>();
    this->m_hurtRightAnimation->addFrame({(int)PLAYER_SIZE.x * 4, posY, (int)PLAYER_SIZE.x, (int)PLAYER_SIZE.y});
    this->m_hurtRightAnimation->setSpriteSheet(spritesheet);
}

bool AA::Player::isAlive() const {
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
    else if (this->m_health == 0) {
        alive = false;
    }
    return alive;
}

bool AA::Player::isVictorious() const {
    bool victorious = false;
    if (this->getPosition().x > this->m_exitArea.left &&
        this->getPosition().y > this->m_exitArea.top &&
        this->getPosition().y < this->m_exitArea.top + this->m_exitArea.height) {
        victorious = true;
    }
    return victorious;
}

void AA::Player::decelerate(const float dt) {
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

void AA::Player::accelerate(const float dt) {
    //öka accelerationen tills dess den når max
    sf::Vector2f acceleration = this->getAcceleration();
    acceleration.x += ACCELERATE_BY * dt;
    if (acceleration.x > MAX_ACCELERATION.x) {
        acceleration.x = MAX_ACCELERATION.x;
    }
    //öka hastigheten beroende på riktningen tills den når max
    sf::Vector2f velocity = this->getVelocity();
    switch (this->m_direction) {
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

void AA::Player::updatePosition(const float dt) {
    sf::Vector2f position = this->getPosition();
    position.x += this->getVelocity().x * dt;
    position.y += this->getVelocity().y * dt;
    this->setPosition(position);
}

void AA::Player::applyGravity(const float dt) {
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

void AA::Player::bounceAgainstSide(const sf::Vector2f &threshold, const sf::Vector2f &distance) {
    sf::Vector2f velocity = this->getVelocity();
    velocity.x *= -1;
    velocity.x *= 0.5;
    this->setVelocity(velocity);

    float overlap = threshold.x - std::abs(distance.x) + this->getBoundingBox().left;
    if (distance.x > 0) overlap *= -1;

    this->move({overlap, 0});
}

void AA::Player::handleMovement(const float dt) {
    switch (this->m_state) {
        case PlayerState::Stationary: {
            this->decelerate(dt);
            this->updatePosition(dt);
        } break;
        case PlayerState::Jumping: {
            sf::Vector2f velocity = this->getVelocity();
            if (velocity.y > 0) {
                this->m_state = PlayerState::Falling;
            } else {
                if ((velocity.x > 0 && this->m_direction == PlayerDirection::Left) || (velocity.x < 0 && this->m_direction == PlayerDirection::Right)) {
                    velocity.x = 0;
                }
                if (velocity.y == 0) {
                    velocity.y = -std::abs(MAX_VELOCITY.y);
                    this->setVelocity(velocity);
                    this->m_jumpSound->play();
                    this->m_isJumping = true;
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

void AA::Player::handleCollision() {
    auto& objectHandler = this->getGame()->getSceneHandler().getActiveScene().getObjectHandler();

    for (unsigned int i = 0; i < objectHandler.getNumberOfObjects(); i++) {
        auto *objectPtr = &objectHandler.getObject(i);

        auto worldPtr = dynamic_cast<World*>(objectPtr);
        if (worldPtr != nullptr) {

            sf::Vector2f threshold;
            threshold.x = (float)worldPtr->getTileSize().y/2 - (float)this->getBoundingBox().left + (float)this->getBoundingBox().width/2;
            threshold.y = (float)worldPtr->getTileSize().y/2 + (float)(this->getBoundingBox().top + this->getBoundingBox().height)/2;

            sf::Vector2f distance = worldPtr->getShortestCollisionDistance(this->getPosition());

            if (std::abs(distance.x) < threshold.x && std::abs(distance.y) < threshold.y) {
                sf::Vector2f velocity = this->getVelocity();
                sf::Vector2f overlap = { threshold.x - std::abs(distance.x), threshold.y - std::abs(distance.y) };
                switch (this->m_state) {
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
                                if (velocity.y >= VELOCITY_HURT_THRESHOLD && !this->m_initialFall && !this->m_hurt) {
                                    this->m_state = PlayerState::Jumping;
                                    this->m_hurt = true;

                                    this->move({0, -overlap.y});
                                    velocity.y = -HURT_VELOCITY.y;
                                    this->setVelocity(velocity);

                                    this->m_health -= 1;
                                    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->m_health);

                                    this->m_hurtSound->play();
                                } else {
                                    if (this->m_initialFall)
                                        this->m_initialFall = false;

                                    this->move({0, -overlap.y});
                                    velocity.y = 0;
                                    this->setVelocity(velocity);
                                    this->m_state = PlayerState::Stationary;

                                    if (this->m_isJumping) {
                                        this->m_isJumping = false;
                                        this->m_wasJumping = true;
                                    }
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
                                this->m_state = PlayerState::Jumping;
                            }
                        }
                    } break;
                }
            } else if (std::abs(distance.x) > threshold.x && distance.y > (PLAYER_SIZE.y-TILE_SIZE.y)/2) {
                this->m_state = PlayerState::Falling;
            }
        }

        auto enemyPtr = dynamic_cast<IEnemy*>(objectPtr);
        if (enemyPtr != nullptr && enemyPtr->isAlive()) {
            float ax = (float)this->getBoundingBox().width/2 + this->getBoundingBox().left;
            float bx = (float)enemyPtr->getBoundingBox().width/2 + enemyPtr->getBoundingBox().left;

            sf::Vector2f diff;
            diff.x = std::abs(enemyPtr->getPosition().x - this->getPosition().x);

            float aPosY = this->getPosition().y + (float)this->getBoundingBox().top/2;
            float bPosY = enemyPtr->getPosition().y + (float)enemyPtr->getBoundingBox().top/2;
            diff.y = std::abs(aPosY - bPosY);

            if (diff.x < ax + bx) {
                sf::Vector2f velocity = this->getVelocity();
                if (this->getPosition().y < enemyPtr->getPosition().y && (diff.y < ((float)this->getBoundingBox().height/2 + enemyPtr->getBoundingBox().top)) && (diff.y > ((float)this->getBoundingBox().height/2 + enemyPtr->getBoundingBox().top)*0.9) && this->m_state == PlayerState::Falling) {
                    enemyPtr->setDead();
                    velocity.y = -(MAX_VELOCITY.y/2);
                }
                else if (((diff.y < (float)this->getBoundingBox().height/2 + enemyPtr->getBoundingBox().top) ||
                          (diff.y < (float)enemyPtr->getBoundingBox().height/2 + this->getBoundingBox().top)) && !this->m_hurt) {
                    this->m_state = PlayerState::Jumping;
                    this->m_hurt = true;

                    velocity.x *= -1;
                    velocity.x *= 0.5;
                    velocity.y = -HURT_VELOCITY.y;

                    this->m_health -= 1;
                    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->m_health);

                    this->m_hurtSound->play();
                }
                this->setVelocity(velocity);
            }
        }

        auto collectiblePtr = dynamic_cast<ICollectible*>(objectPtr);
        if (collectiblePtr != nullptr) {
            sf::Vector2f threshold;
            threshold.x = 70.f/2 - 10 - (float)this->getBoundingBox().left + (float)this->getBoundingBox().width/2;
            threshold.y = 70.f/2 - 10 + (float)(this->getBoundingBox().top + this->getBoundingBox().height)/2;

            sf::Vector2f distance;
            distance.x = std::abs(collectiblePtr->getPosition().x - this->getPosition().x);
            distance.y = std::abs(collectiblePtr->getPosition().y - this->getPosition().y);

            if (std::abs(distance.x) < threshold.x && distance.y < threshold.y && !collectiblePtr->isCollected()) {
                auto *coin = dynamic_cast<CollectibleCoin*>(collectiblePtr);
                if (coin != nullptr) {
                    this->m_coins += 1;
                    this->getGame()->getPropertyHandler().set<unsigned int>("coins", this->m_coins);
                }
                auto *healthPtr = dynamic_cast<CollectibleHealth*>(collectiblePtr);
                if (healthPtr != nullptr) {
                    this->m_health += 1;
                    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->m_health);
                }
                collectiblePtr->setCollected(true);
            }
        }
    }
}

void AA::Player::handleAnimation(const float dt) {
    auto* entity = &this->getEntity(0);
    auto* animatedEntity = dynamic_cast<CGL::AnimatedEntity*>(entity);
    if (animatedEntity == nullptr)
        return;

    const CGL::Animation* nextAnimation = nullptr;
    switch (this->m_state) {
        case PlayerState::Stationary: {
            if (this->getVelocity().x == 0) {
                nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_stationaryLeftAnimation.get() : this->m_stationaryRightAnimation.get();
            } else {
                nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_walkLeftAnimation.get() : this->m_walkRightAnimation.get();
            }
        } break;
        case PlayerState::Walking: {
            nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_walkLeftAnimation.get() : this->m_walkRightAnimation.get();
        } break;
        case PlayerState::Jumping: {
            if (this->m_hurt) {
                nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_hurtLeftAnimation.get() : this->m_hurtRightAnimation.get();
            } else {
                nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_jumpLeftAnimation.get() : this->m_jumpRightAnimation.get();
            }
        } break;
        case PlayerState::Falling: {
            if (this->m_hurt) {
                nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_hurtLeftAnimation.get() : this->m_hurtRightAnimation.get();
            } else {
                nextAnimation = this->m_direction == PlayerDirection::Left ? this->m_jumpLeftAnimation.get() : this->m_jumpRightAnimation.get();
            }
        } break;
    }

    if (nextAnimation != animatedEntity->getAnimation()) {
        animatedEntity->play(*nextAnimation);
        switch (this->m_direction) {
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
    if (this->m_hurt) {
        int currentFlash = (int)(this->m_timeSinceHurt / HURT_FLASH_SPEED) + 1;
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

void AA::Player::restore(const bool respawn) {
    if (!respawn) {
        this->m_currentCharacter = std::bind(std::uniform_int_distribution<>(0,4),std::default_random_engine(std::random_device{}()))();
    }
    this->setupAnimations();

    this->setAcceleration({0, 0});
    this->setVelocity({0, 1});

    int spawnIndex = 0;
    for (int i = 0; i < this->m_spawnAreas.size() && respawn; i++) {
        if (this->getPosition().x >= this->m_spawnAreas[i].left) {
            spawnIndex = i;
        }
    }
    sf::Vector2f position;
    position.x = (float)m_spawnAreas[spawnIndex].left+(float)this->getBoundingBox().width/2;
    position.y = 0;
    this->setPosition(position);

    this->setVisible(false);

    this->m_state = PlayerState::Falling;
    this->m_direction = PlayerDirection::Right;
    this->m_hurt = false;
    this->m_initialFall = true;

    this->m_isJumping = false;
    this->m_wasJumping = false;

    this->m_timeSinceNewGame = 0;
    this->m_timeSinceGameOver = 0;
    this->m_timeSinceHurt = 0;

    this->m_health = 3;
    this->getGame()->getPropertyHandler().set<unsigned int>("health", this->m_health);

    if (!respawn) {
        this->m_coins = 0;
        this->getGame()->getPropertyHandler().set<unsigned int>("coins", this->m_coins);
    }
}

void AA::Player::processEvents() {
    if (!this->isVictorious() && this->isAlive()) {
        bool leftPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Left).down;
        bool rightPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Right).down;
        bool spacePressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Space).pressed;
        switch (this->m_state) {
            case PlayerState::Stationary:
                if (leftPressed != rightPressed) {
                    this->m_state = PlayerState::Walking;
                    if (leftPressed) {
                        this->m_direction = PlayerDirection::Left;
                    }
                    if (rightPressed) {
                        this->m_direction = PlayerDirection::Right;
                    }
                } else if (spacePressed) {
                    this->m_state = PlayerState::Jumping;
                }
                break;
            case PlayerState::Walking:
                if (leftPressed != rightPressed) {
                    if (leftPressed) {
                        this->m_direction = PlayerDirection::Left;
                    }
                    if (rightPressed) {
                        this->m_direction = PlayerDirection::Right;
                    }
                }
                if (leftPressed == rightPressed) {
                    this->m_state = PlayerState::Stationary;
                }
                if (spacePressed) {
                    this->m_state = PlayerState::Jumping;
                }
                break;
            default:
                break;
        }
    }
}

void AA::Player::update(const float dt) {
    if (this->isVisible()) {
        this->handleMovement(dt);
        this->handleAnimation(dt);
    }

    if (this->m_hurt) {
        this->m_timeSinceHurt += dt;
        if (this->m_timeSinceHurt >= HURT_DURATION) {
            this->m_timeSinceHurt = 0;
            this->m_hurt = false;
        }
    }

    if (this->m_timeSinceNewGame >= SPAWN_DELAY) {
        if (this->m_timeSinceNewGame != 0) {
            this->m_timeSinceNewGame = 0;
            this->setVisible(true);
        }
    } else if (!this->isVisible()) {
        this->m_timeSinceNewGame += dt;
    }
    if (this->isVisible() && this->isAlive()) {
        this->handleCollision();
    }

    if (this->isVictorious() && this->isAlive()) {
        if (this->getVelocity().y == 0) {
            this->m_state = PlayerState::Walking;
            this->m_direction = PlayerDirection::Right;
        }
        if (this->m_timeSinceGameOver == 0) {
            this->m_victoriousSound->play();
        }
        this->m_timeSinceGameOver += dt;
        if (this->m_timeSinceGameOver >= 0.5) {
            this->getGame()->getPropertyHandler().set<bool>("levelComplete", true);
        }
    }
    else if (!this->isAlive() && !this->isVictorious()) {
        if (this->m_timeSinceGameOver == 0) {
            this->getGame()->getPropertyHandler().set<unsigned int>("health", 0);
            this->m_gameOverSound->play();
        }
        this->m_timeSinceGameOver += dt;
        if (this->m_timeSinceGameOver >= 1) {
            this->getGame()->getPropertyHandler().set<bool>("gameOver", true);
        }
    }

    auto newCenter = this->getPosition();
    if (this->m_isJumping) {
        auto cameraCenter = this->getGame()->getWindowHandler().getCamera().getCenter();
        newCenter.y = cameraCenter.y;
    }
    if (this->m_wasJumping) {
        this->m_wasJumping = false;
    }
    this->getGame()->getWindowHandler().getCamera().setCenter(newCenter);
}
