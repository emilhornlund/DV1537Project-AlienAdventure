/**
 * @file AnimationSequence.cpp
 * @date 2016-12-01
 * @author Emil Hörnlund
 */

#include "AnimationSequence.hpp"
#include "AnimationFrame.hpp"

AnimationSequence::AnimationSequence(std::string id, std::string filename) {
    this->filename = filename;
    this->spriteSheet = new sf::Texture;
    if (!this->spriteSheet->loadFromFile(filename)) {
        throw "Failed to load " + filename;
    }

    this->identifier = id;

    this->timeSinceLastFrame = 0;
    this->currentFrame = 0;

    this->framesCapacity = 0;
    this->framesSize = 0;
    this->frames = new AnimationFrame*[this->framesCapacity];
}

AnimationSequence::AnimationSequence(const AnimationSequence &original) {
    this->filename = original.filename;
    this->spriteSheet = new sf::Texture(*original.spriteSheet);

    this->identifier = original.getIdentifier();

    this->framesCapacity = original.framesCapacity;
    this->framesSize = original.framesSize;
    this->frames = new AnimationFrame*[this->framesCapacity];
    for (int i = 0; i < this->framesSize; i++) {
        this->frames[i] = original.frames[i]->clone();
        this->frames[i]->setTexture(*this->spriteSheet);
    }

    this->timeSinceLastFrame = original.timeSinceLastFrame;
    this->currentFrame = original.currentFrame;
}

AnimationSequence::~AnimationSequence() {
    delete this->spriteSheet;
    this->spriteSheet = nullptr;

    this->clearFrames();
}

AnimationSequence& AnimationSequence::operator=(const AnimationSequence &original) {
    if (this != &original) {
        this->clearFrames();

        this->filename = original.filename;

        delete this->spriteSheet;
        this->spriteSheet = new sf::Texture(*original.spriteSheet);

        this->identifier = original.getIdentifier();

        this->framesCapacity = original.framesCapacity;
        this->framesSize = original.framesSize;
        this->frames = new AnimationFrame*[this->framesCapacity];
        for (int i = 0; i < this->framesSize; i++) {
            this->frames[i] = original.frames[i]->clone();
        }

        this->timeSinceLastFrame = original.timeSinceLastFrame;
        this->currentFrame = original.currentFrame;
    }
    return *this;
}

AnimationSequence* AnimationSequence::clone() const {
    return new AnimationSequence(*this);
}

void AnimationSequence::setIdentifier(const std::string &id) {
    this->identifier = id;
}

std::string AnimationSequence::getIdentifier() const {
    return this->identifier;
}

void AnimationSequence::addFrame(const sf::IntRect &rect, const float duration, const sf::Vector2f scale) {
    if (this->framesCapacity == this->framesSize) {
        this->framesCapacity += 5;
        auto **tempFrames = new AnimationFrame*[this->framesCapacity];
        for (int i = 0; i < this->framesSize; i++) {
            tempFrames[i] = this->frames[i]->clone();
        }
        this->clearFrames();
        this->frames = tempFrames;
    }
    auto *frame = new AnimationFrame(duration);
    frame->setOrigin(rect.width/2.0f, rect.height/2.0f);
    frame->setTextureRect(rect);
    frame->setTexture(*this->spriteSheet);
    frame->setScale(scale);
    this->frames[this->framesSize] = frame;
    this->framesSize++;
}

void AnimationSequence::updateFrames(const float dt, sf::Color color) {
    this->timeSinceLastFrame += dt;

    float duration = this->frames[this->currentFrame]->getDuration();
    this->frames[this->currentFrame]->setColor(color);

    if (this->timeSinceLastFrame >= duration) {
        this->timeSinceLastFrame = 0;
        this->currentFrame++;
        if (this->currentFrame >= this->framesSize) {
            this->currentFrame = 0;
        }
    }
}

AnimationFrame* AnimationSequence::getCurrentFrame() {
    AnimationFrame* frame = nullptr;
    if (this->currentFrame >= 0 && this->currentFrame < this->framesSize) {
        frame = this->frames[this->currentFrame];
    }
    return frame;
}

int AnimationSequence::numberOfFrames() const {
    return this->framesSize;
}

void AnimationSequence::clearFrames() {
    for (int i = 0; i < this->framesSize; i++) {
        delete this->frames[i];
        this->frames[i] = nullptr;
    }
    delete[] this->frames;
    this->frames = nullptr;
}
