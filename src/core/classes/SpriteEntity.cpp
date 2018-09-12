//
// Created by Emil Hörnlund on 2018-09-08.
//

#include "core/classes/SpriteEntity.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

SpriteEntity::SpriteEntity() : IEntity() {}

SpriteEntity::~SpriteEntity() = default;

void SpriteEntity::setTextureRect(const sf::IntRect &rectangle) {
    this->m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    this->m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rectangle.height));
    this-> m_vertices[2].position = sf::Vector2f(static_cast<float>(rectangle.width), static_cast<float>(rectangle.height));
    this->m_vertices[3].position = sf::Vector2f(static_cast<float>(rectangle.width), 0.f);

    auto left = static_cast<float>(rectangle.left) + 0.0001f;
    auto right = left + static_cast<float>(rectangle.width);
    auto top = static_cast<float>(rectangle.top);
    auto bottom = top + static_cast<float>(rectangle.height);

    this->m_vertices[0].texCoords = sf::Vector2f(left, top);
    this->m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    this->m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    this->m_vertices[3].texCoords = sf::Vector2f(right, top);
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
