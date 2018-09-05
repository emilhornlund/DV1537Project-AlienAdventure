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

enum EnemyType { SlimePurple = 1, SlimeGreen = 2, SlimeBlue = 3, FishGreen = 4, FishPink = 5, FishBlue = 6, Bee = 7, BeeBlack = 8, Snail = 9, SnailMushroom = 10, Mouse = 11, Frog = 13, WormGreen = 14, WormPink = 15 };

class Enemy : public GameObject {
private:
    EnemyType type;

    sf::IntRect spawnArea;

    bool alive;

    sf::SoundBuffer* soundBuffer;

    sf::Sound* sound;

    void setupInitialPositionAndBoundingBoxes();

    void setupAnimation();

    void handleMovement(const float dt);

    void handleAnimation(const float dt);
public:
    Enemy(Game *game, const sf::IntRect spawnArea, const EnemyType type = SlimeGreen);

    Enemy(const Enemy &original);

    ~Enemy() override;

    virtual Enemy& operator=(const Enemy &original);

    Enemy* clone() const override;

    bool isAlive();

    void setDead();

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Enemy_hpp */
