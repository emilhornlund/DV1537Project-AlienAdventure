/**
 * @file Collectible.hpp
 * @date 2016-12-09
 * @author Emil Hörnlund
 */

#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include <SFML/Audio.hpp>

#include "Core.hpp"
#include "GameObject.hpp"

class Collectible : public GameObject {
public:
    enum class CollectibleType { GoldCoin, Life };
private:
    CollectibleType type;

    sf::IntRect spawnArea;

    bool collected;

    sf::SoundBuffer* soundBuffer;

    sf::Sound* sound;
public:
    Collectible(Game *game, const sf::IntRect spawnArea, const Collectible::CollectibleType type = Collectible::CollectibleType::GoldCoin);

    Collectible(const Collectible &original);

    ~Collectible() override;

    virtual Collectible& operator=(const Collectible &original);

    Collectible* clone() const override;

    Collectible::CollectibleType getType() const;

    bool isCollected() const;

    void setCollected();

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Collectible_hpp */
