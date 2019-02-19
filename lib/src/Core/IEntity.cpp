//
// Created by Emil Hörnlund on 2018-09-07.
//

#include <Core/IEntity.hpp>

CGL::IEntity::IEntity() = default;

CGL::IEntity::~IEntity() = default;

void CGL::IEntity::setTexture(const sf::Texture &texture) {
    this->m_texture = &texture;
}

const sf::Texture &CGL::IEntity::getTexture() const {
    return *this->m_texture;
}

void CGL::IEntity::setOffset(const sf::Vector2f &offset) {
    this->m_offset = offset;
}

void CGL::IEntity::setOffset(const float x, const float y) {
    this->m_offset = {x, y};
}

const sf::Vector2f &CGL::IEntity::getOffset() const {
    return this->m_offset;
}
