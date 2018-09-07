/**
 * @file AnimationSequence.hpp
 * @date 2016-12-01
 * @author Emil Hörnlund
 */

#ifndef ANIMATION_SEQUENCE_HPP
#define ANIMATION_SEQUENCE_HPP

#include <memory>
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

    std::vector<std::shared_ptr<AnimationFrame>> frames;

    AnimationSequence(const AnimationSequence &original);

    AnimationSequence& operator=(const AnimationSequence &original);
public:
    AnimationSequence(Game *game, std::string id, std::string filename);

    virtual ~AnimationSequence();

    Game* getGame() const;

    void setIdentifier(const std::string &id);

    std::string getIdentifier() const;

    void addFrame(const sf::IntRect &rect, const float duration = 0, const sf::Vector2f scale = {1, 1});

    void updateFrames(const float dt, sf::Color color = sf::Color(255, 255, 255, 255));

    AnimationFrame& getCurrentFrame();

    int getNumberOfFrames() const;

    void clearFrames();
};

#endif /* AnimationSequence_hpp */
