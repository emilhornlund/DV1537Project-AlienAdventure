/**
 * @file Enemy.hpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../../../lib/include/interfaces/IGameObject.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Animation;

class IEnemy : public IGameObject {
public:
    enum class EnemyDirection { None, Left, Right };
private:
    EnemyDirection m_direction;

    sf::IntRect m_spawnArea;

    bool m_alive;

    sf::SoundBuffer* m_soundBuffer;

    sf::Sound* m_sound;

    IEnemy(const IEnemy &original);

    IEnemy& operator=(const IEnemy &original);

    void handleMovement(const float dt);

    void handleAnimation(const float dt);

    virtual const Animation& getMovingAnimation() const = 0;

    virtual const Animation& getDeadAnimation() const = 0;
public:
    IEnemy(IGame *game, const sf::IntRect &spawnArea);

    ~IEnemy() override = 0;

    const EnemyDirection& getDirection() const;

    bool isAlive();

    void setDead();

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Enemy_hpp */
