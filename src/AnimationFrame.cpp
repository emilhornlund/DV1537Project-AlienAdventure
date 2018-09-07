/**
 * @file AnimationFrame.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "AnimationFrame.hpp"

AnimationFrame::AnimationFrame(float duration) {
    this->duration = duration;
}

AnimationFrame::~AnimationFrame() = default;

void AnimationFrame::setDuration(const float duration) {
    this->duration = duration;
}

float AnimationFrame::getDuration() const {
    return this->duration;
}
