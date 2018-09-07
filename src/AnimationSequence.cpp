/**
 * @file AnimationSequence.cpp
 * @date 2016-12-01
 * @author Emil Hörnlund
 */

#include "AnimationSequence.hpp"
#include "AnimationFrame.hpp"
#include "Game.hpp"
#include "ResourceHandler.hpp"

AnimationSequence::AnimationSequence(Game *game, std::string id, std::string filename) {
    this->game = game;

    this->filename = filename;

    if (!this->getGame()->getTextureResourceHandler()->isLoaded(filename))
        this->getGame()->getTextureResourceHandler()->load(filename);
    this->spriteSheet = &this->getGame()->getTextureResourceHandler()->get(filename);

    this->identifier = id;

    this->timeSinceLastFrame = 0;
    this->currentFrame = 0;
}

AnimationSequence::~AnimationSequence() {
    this->clearFrames();
}

Game* AnimationSequence::getGame() const {
    return this->game;
}

void AnimationSequence::setIdentifier(const std::string &id) {
    this->identifier = id;
}

std::string AnimationSequence::getIdentifier() const {
    return this->identifier;
}

void AnimationSequence::addFrame(const sf::IntRect &rect, const float duration, const sf::Vector2f scale) {
    std::shared_ptr<AnimationFrame> sharedPtr = std::make_shared<AnimationFrame>(duration);
    sharedPtr->setOrigin(rect.width/2.0f, rect.height/2.0f);
    sharedPtr->setTextureRect(rect);
    sharedPtr->setTexture(*this->spriteSheet);
    sharedPtr->setScale(scale);
    this->frames.push_back(sharedPtr);
}

void AnimationSequence::updateFrames(const float dt, sf::Color color) {
    this->timeSinceLastFrame += dt;

    float duration = this->frames[this->currentFrame]->getDuration();
    this->frames[this->currentFrame]->setColor(color);

    if (this->timeSinceLastFrame >= duration) {
        this->timeSinceLastFrame = 0;
        this->currentFrame++;
        if (this->currentFrame >= this->frames.size()) {
            this->currentFrame = 0;
        }
    }
}

AnimationFrame & AnimationSequence::getCurrentFrame() {
    return *this->frames[this->currentFrame];
}

int AnimationSequence::getNumberOfFrames() const {
    return this->frames.size();
}

void AnimationSequence::clearFrames() {
    this->frames.clear();
}
