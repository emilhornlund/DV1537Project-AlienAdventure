//
// Created by Emil Hörnlund on 2018-09-07.
//

#include <Core/AnimatedEntity.hpp>
#include <Core/Animation.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

CGL::AnimatedEntity::AnimatedEntity(const bool paused) : m_animation(nullptr),
                                                          m_currentFrame(0),
                                                          m_isPaused(paused) {}

CGL::AnimatedEntity::~AnimatedEntity() = default;

void CGL::AnimatedEntity::setAnimation(const CGL::Animation &animation) {
    this->m_animation = &animation;
    this->setTexture(*this->m_animation->getSpriteSheet());
    this->m_currentFrame = 0;
    this->setFrame(this->m_currentFrame);
}

void CGL::AnimatedEntity::play() {
    this->m_isPaused = false;
}

void CGL::AnimatedEntity::play(const CGL::Animation &animation) {
    if (this->getAnimation() != &animation)
        this->setAnimation(animation);
    this->play();
}

void CGL::AnimatedEntity::pause() {
    this->m_isPaused = true;
}

void CGL::AnimatedEntity::stop() {
    this->m_isPaused = true;
    this->m_currentFrame = 0;
    this->setFrame(this->m_currentFrame);
}

const CGL::Animation *CGL::AnimatedEntity::getAnimation() const {
    return this->m_animation;
}

const sf::FloatRect CGL::AnimatedEntity::getLocalBounds() const {
    const auto& rect = this->m_animation->getFrame(this->m_currentFrame);
    return sf::FloatRect(0.f, 0.f, std::abs(rect.width), std::abs(rect.height));
}

const sf::FloatRect CGL::AnimatedEntity::getGlobalBounds() const {
    return this->getTransform().transformRect(this->getLocalBounds());
}

bool CGL::AnimatedEntity::isPlaying() const {
    return !this->m_isPaused;
}

void CGL::AnimatedEntity::setFrame(std::size_t newFrame, bool resetTime) {
    if (this->m_animation) {
        sf::IntRect rect = this->m_animation->getFrame(newFrame);

        this->m_vertices[0].position = sf::Vector2f(0.f, 0.f);
        this->m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        this->m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        this->m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        float left = static_cast<float>(rect.left) + 0.0001f;
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        this->m_vertices[0].texCoords = sf::Vector2f(left, top);
        this->m_vertices[1].texCoords = sf::Vector2f(left, bottom);
        this->m_vertices[2].texCoords = sf::Vector2f(right, bottom);
        this->m_vertices[3].texCoords = sf::Vector2f(right, top);
    }

    if (resetTime) {
        this->m_currentTime = sf::Time::Zero;
    }
}

void CGL::AnimatedEntity::update(sf::Time deltaTime) {
    if (!this->m_isPaused && this->m_animation) {
        this->m_currentTime += deltaTime;
        if (this->m_currentTime >= this->m_animation->getFrameTime()) {
            this->m_currentTime = sf::microseconds(this->m_currentTime.asMicroseconds() % this->m_animation->getFrameTime().asMicroseconds());
            if (this->m_currentFrame + 1 < this->m_animation->getSize()) {
                this->m_currentFrame++;
            } else {
                this->m_currentFrame = 0;
                if (!this->m_animation->isLooped()) {
                    m_isPaused = true;
                }
            }
            this->setFrame(this->m_currentFrame, false);
        }
    }
}

void CGL::AnimatedEntity::setColor(const sf::Color &color) {
    this->m_vertices[0].color = color;
    this->m_vertices[1].color = color;
    this->m_vertices[2].color = color;
    this->m_vertices[3].color = color;
}

void CGL::AnimatedEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (this->m_animation) {
        states.transform *= getTransform();
        states.texture = &this->getTexture();
        target.draw(this->m_vertices, 4, sf::Quads, states);
    }
}
