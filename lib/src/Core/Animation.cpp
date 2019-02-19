//
// Created by Emil Hörnlund on 2018-09-08.
//

#include <Core/Animation.hpp>

#include <SFML/Graphics/Texture.hpp>

CGL::Animation::Animation(sf::Time frameTime, bool looped) : m_frameTime(frameTime),
                                                              m_isLooped(looped),
                                                              m_texture(nullptr) {}

CGL::Animation::~Animation() = default;

void CGL::Animation::addFrame(const sf::IntRect &rect) {
    this->m_frames.push_back(rect);
}

void CGL::Animation::setSpriteSheet(const sf::Texture &texture) {
    this->m_texture = &texture;
}

const sf::Texture *CGL::Animation::getSpriteSheet() const {
    return this->m_texture;
}

unsigned long CGL::Animation::getSize() const {
    return this->m_frames.size();
}

const sf::IntRect &CGL::Animation::getFrame(unsigned long index) const {
    return this->m_frames.at(index);
}

void CGL::Animation::setFrameTime(sf::Time time) {
    this->m_frameTime = time;
}

sf::Time CGL::Animation::getFrameTime() const {
    return this->m_frameTime;
}

void CGL::Animation::setLooped(bool looped) {
    this->m_isLooped = looped;
}

bool CGL::Animation::isLooped() const {
    return this->m_isLooped;
}
