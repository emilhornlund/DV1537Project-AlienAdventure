/**
 * @file AnimationFrame.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "AnimationFrame.hpp"

AnimationFrame::AnimationFrame(float duration) {
    this->duration = duration;
}

AnimationFrame::AnimationFrame(const AnimationFrame &original) {
    this->duration = original.duration;
    this->setTextureRect(original.getTextureRect());
    this->setTexture(*original.getTexture());
    this->setOrigin(original.getOrigin());
    this->setScale(original.getScale());
}

AnimationFrame::~AnimationFrame() = default;

AnimationFrame& AnimationFrame::operator=(const AnimationFrame &original) {
    if (this != &original) {
        this->duration = original.getDuration();
        this->setTextureRect(original.getTextureRect());
        this->setTexture(*original.getTexture());
        this->setOrigin(original.getOrigin());
        this->setScale(original.getScale());
    }
    return *this;
}

AnimationFrame* AnimationFrame::clone() const {
    return new AnimationFrame(*this);
}

void AnimationFrame::setDuration(const float duration) {
    this->duration = duration;
}

float AnimationFrame::getDuration() const {
    return this->duration;
}
