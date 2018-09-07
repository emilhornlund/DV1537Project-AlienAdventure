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
private:
    sf::IntRect spawnArea;

    bool collected;

    sf::SoundBuffer* soundBuffer;

    sf::Sound* sound;

    Collectible(const Collectible &original);

    Collectible& operator=(const Collectible &original);
public:
    Collectible(Game *game, const sf::IntRect spawnArea, const std::string &soundFilePath);

    ~Collectible() override = 0;

    bool isCollected() const;

    void setCollected(const bool collected);

    void restore(const bool respawn) override = 0;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* Collectible_hpp */
