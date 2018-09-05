/**
 * @file AnimationSequence.hpp
 * @date 2016-12-01
 * @author Emil Hörnlund
 */

#ifndef ANIMATION_SEQUENCE_HPP
#define ANIMATION_SEQUENCE_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class AnimationSequence {
private:
    Game* game;

    std::string filename;

    sf::Texture* spriteSheet;

    std::string identifier;

    float timeSinceLastFrame;

    int currentFrame;

    unsigned int framesCapacity;

    unsigned int framesSize;

    AnimationFrame** frames;
public:
    AnimationSequence(Game *game, std::string id, std::string filename);

    AnimationSequence(const AnimationSequence &original);

    virtual ~AnimationSequence();

    virtual AnimationSequence& operator=(const AnimationSequence &original);

    virtual AnimationSequence* clone() const;

    Game* getGame() const;

    void setIdentifier(const std::string &id);

    std::string getIdentifier() const;

    void addFrame(const sf::IntRect &rect, const float duration = 0, const sf::Vector2f scale = {1, 1});

    void updateFrames(const float dt, sf::Color color = sf::Color(255, 255, 255, 255));

    AnimationFrame* getCurrentFrame();

    int numberOfFrames() const;

    void clearFrames();
};

#endif /* AnimationSequence_hpp */
