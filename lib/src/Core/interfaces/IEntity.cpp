//
// Created by Emil Hörnlund on 2018-09-07.
//

#include "../../include/interfaces/IEntity.hpp"

IEntity::IEntity() = default;

IEntity::~IEntity() = default;

void IEntity::setTexture(const sf::Texture &texture) {
    this->m_texture = &texture;
}

const sf::Texture &IEntity::getTexture() const {
    return *this->m_texture;
}

void IEntity::setOffset(const sf::Vector2f &offset) {
    this->m_offset = offset;
}

void IEntity::setOffset(const float x, const float y) {
    this->m_offset = {x, y};
}

const sf::Vector2f &IEntity::getOffset() const {
    return this->m_offset;
}
