/**
 * @file Player.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Core/interfaces/IGameObject.hpp>

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
    PlayerState m_state;

    PlayerDirection m_direction;

    std::vector<sf::IntRect> m_spawnAreas;

    sf::IntRect m_exitArea;

    bool m_hurt;

    bool m_initialFall;

    int m_currentCharacter;

    float m_timeSinceNewGame;

    float m_timeSinceHurt;

    float m_timeSinceGameOver;

    bool m_isJumping;

    bool m_wasJumping;

    unsigned int m_health;

    unsigned int m_coins;

    sf::SoundBuffer* m_jumpSoundBuffer;

    std::shared_ptr<sf::Sound> m_jumpSound;

    sf::SoundBuffer* m_hurtSoundBuffer;

    std::shared_ptr<sf::Sound> m_hurtSound;

    sf::SoundBuffer* m_gameOverSoundBuffer;

    std::shared_ptr<sf::Sound> m_gameOverSound;

    sf::SoundBuffer* m_victoriousSoundBuffer;

    std::shared_ptr<sf::Sound> m_victoriousSound;

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
public:
    Player(IGame *game, const std::vector<sf::IntRect> &spawnAreas, const sf::IntRect &exitArea);

    ~Player() override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Player_h */
