/**
 * @file Enemy.hpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Audio.hpp>

#include "Core.hpp"
#include "GameObject.hpp"

class Enemy : public GameObject {
private:
    sf::IntRect spawnArea;

    bool alive;

    sf::SoundBuffer* soundBuffer;

    sf::Sound* sound;

    Enemy(const Enemy &original);

    Enemy& operator=(const Enemy &original);

    void handleMovement(const float dt);

    void handleAnimation(const float dt);
public:
    Enemy(Game *game, const sf::IntRect spawnArea);

    ~Enemy() override;

    virtual void configure() = 0;

    bool isAlive();

    void setDead();

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Enemy_hpp */
