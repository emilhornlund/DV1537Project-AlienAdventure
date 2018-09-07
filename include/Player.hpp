/**
 * @file Player.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Audio.hpp>

#include "Core.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
public:
    enum class PlayerState { Stationary, Falling, Jumping, Walking };

    enum class PlayerDirection { Left, Right };
private:
    PlayerState state;

    PlayerDirection direction;

    std::vector<sf::IntRect> spawnAreas;

    sf::IntRect exitArea;

    bool isHurt;

    bool initialFall;

    int currentCharacter;

    float timeSinceNewGame;

    float timeSinceHurt;

    float timeSinceGameOver;

    unsigned int health;

    unsigned int coins;

    sf::SoundBuffer* jumpSoundBuffer;

    sf::Sound* jumpSound;

    sf::SoundBuffer* hurtSoundBuffer;

    sf::Sound* hurtSound;

    sf::SoundBuffer* gameOverSoundBuffer;

    sf::Sound* gameOverSound;

    sf::SoundBuffer* victoriousSoundBuffer;

    sf::Sound* victoriousSound;

    Player(const Player &original);

    Player& operator=(const Player &original);

    void setupSounds();

    void setupAnimations() const;

    bool isAlive() const;

    bool isVictorious() const;

    void decelerate(const float dt);

    void accelerate(const float dt);

    void updatePosition(const float dt);

    void applyGravity(const float dt);

    void bounceAgainstSide(const sf::Vector2f threshold, const sf::Vector2f distance);

    void handleMovement(const float dt);

    void handleCollision();

    void handleAnimation(const float dt);

    void updateCameraAndBackground();
public:
    Player(Game *game, const std::vector<sf::IntRect> &spawnAreas, const sf::IntRect exitArea);

    ~Player() override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Player_h */
