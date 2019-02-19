//
// Created by Emil Hörnlund on 2018-09-08.
//

#include <Core/classes/SpriteEntity.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

SpriteEntity::SpriteEntity() : IEntity() {}

SpriteEntity::~SpriteEntity() = default;

void SpriteEntity::setTextureRect(const sf::IntRect &rect) {
    this->m_textureRect = rect;

    this->m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    this->m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
    this-> m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
    this->m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

    auto left = static_cast<float>(rect.left) + 0.0001f;
    auto right = left + static_cast<float>(rect.width);
    auto top = static_cast<float>(rect.top);
    auto bottom = top + static_cast<float>(rect.height);

    this->m_vertices[0].texCoords = sf::Vector2f(left, top);
    this->m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    this->m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    this->m_vertices[3].texCoords = sf::Vector2f(right, top);
}

const sf::IntRect& SpriteEntity::getTextureRect() const {
    return this->m_textureRect;
}

void SpriteEntity::setColor(const sf::Color &color) {
    this->m_vertices[0].color = color;
    this->m_vertices[1].color = color;
    this->m_vertices[2].color = color;
    this->m_vertices[3].color = color;
}

void SpriteEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &this->getTexture();
    target.draw(this->m_vertices, 4, sf::Quads, states);
}
