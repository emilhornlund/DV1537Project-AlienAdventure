//
// Created by Emil Hörnlund on 2018-09-08.
//

#include "../../include/classes/Animation.hpp"

#include <SFML/Graphics/Texture.hpp>

Animation::Animation(sf::Time frameTime, bool looped) : m_frameTime(frameTime),
                                                        m_isLooped(looped),
                                                        m_texture(nullptr) {}

Animation::~Animation() = default;

void Animation::addFrame(const sf::IntRect &rect) {
    this->m_frames.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture &texture) {
    this->m_texture = &texture;
}

const sf::Texture *Animation::getSpriteSheet() const {
    return this->m_texture;
}

unsigned long Animation::getSize() const {
    return this->m_frames.size();
}

const sf::IntRect &Animation::getFrame(unsigned long index) const {
    return this->m_frames.at(index);
}

void Animation::setFrameTime(sf::Time time) {
    this->m_frameTime = time;
}

sf::Time Animation::getFrameTime() const {
    return this->m_frameTime;
}

void Animation::setLooped(bool looped) {
    this->m_isLooped = looped;
}

bool Animation::isLooped() const {
    return this->m_isLooped;
}
