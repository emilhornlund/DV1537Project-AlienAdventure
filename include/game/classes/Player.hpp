/**
 * @file Player.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "core/interfaces/IGameObject.hpp"

#include <memory>

class Animation;

namespace sf {
    class Sound;
    class SoundBuffer;
}

class Player : public IGameObject {
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

    std::shared_ptr<sf::Sound> jumpSound;

    sf::SoundBuffer* hurtSoundBuffer;

    std::shared_ptr<sf::Sound> hurtSound;

    sf::SoundBuffer* gameOverSoundBuffer;

    std::shared_ptr<sf::Sound> gameOverSound;

    sf::SoundBuffer* victoriousSoundBuffer;

    std::shared_ptr<sf::Sound> victoriousSound;

    std::shared_ptr<Animation> m_stationaryLeftAnimation;

    std::shared_ptr<Animation> m_stationaryRightAnimation;

    std::shared_ptr<Animation> m_walkLeftAnimation;

    std::shared_ptr<Animation> m_walkRightAnimation;

    std::shared_ptr<Animation> m_jumpLeftAnimation;

    std::shared_ptr<Animation> m_jumpRightAnimation;

    std::shared_ptr<Animation> m_hurtLeftAnimation;

    std::shared_ptr<Animation> m_hurtRightAnimation;

    Player(const Player &original);

    Player& operator=(const Player &original);

    void setupSounds();

    void setupAnimations();

    bool isAlive() const;

    bool isVictorious() const;

    void decelerate(const float dt);

    void accelerate(const float dt);

    void updatePosition(const float dt);

    void applyGravity(const float dt);

    void bounceAgainstSide(const sf::Vector2f &threshold, const sf::Vector2f &distance);

    void handleMovement(const float dt);

    void handleCollision();

    void handleAnimation(const float dt);

    void updateCameraAndBackground();
public:
    Player(IGame *game, const std::vector<sf::IntRect> &spawnAreas, const sf::IntRect &exitArea);

    ~Player() override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Player_h */
