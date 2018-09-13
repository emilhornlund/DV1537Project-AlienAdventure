/**
 * @file GameObject.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "core/interfaces/IEntity.hpp"
#include "core/interfaces/IGame.hpp"
#include "core/interfaces/IGameObject.hpp"

#include <SFML/Graphics/Sprite.hpp>

IGameObject::IGameObject(IGame *game, const int zIndex, const bool useCamera) : m_game(game),
                                                                                   m_zIndex(zIndex),
                                                                                   m_visible(true),
                                                                                   m_useCamera(useCamera),
                                                                                   m_position(sf::Vector2f(0,0)),
                                                                                   m_velocity(sf::Vector2f(0,0)),
                                                                                   m_acceleration(sf::Vector2f(0,0)),
                                                                                   m_boundingBox(sf::IntRect(0,0,0,0)) {

}

IGameObject::~IGameObject() = default;

IGame* IGameObject::getGame() const {
    return this->m_game;
}

void IGameObject::addEntity(std::shared_ptr<IEntity> entity) {
    this->m_entities.push_back(entity);
}

unsigned long IGameObject::getEntitiesSize() const {
    return this->m_entities.size();
}

IEntity& IGameObject::getEntity(unsigned long index) const {
    return *this->m_entities.at(index);
}

void IGameObject::clearEntities() {
    this->m_entities.clear();
}

int IGameObject::getZIndex() const {
    return this->m_zIndex;
}

void IGameObject::setZIndex(const int depth) {
    this->m_zIndex = depth;
}

bool IGameObject::isVisible() const {
    return m_visible;
}

void IGameObject::setVisible(const bool visible) {
    this->m_visible = visible;
}

bool IGameObject::isUsingCamera() const {
    return this->m_useCamera;
}

void IGameObject::setPosition(const sf::Vector2f &position) {
    this->m_position = position;
}

void IGameObject::move(const sf::Vector2f &moveBy) {
    this->m_position += moveBy;
}

sf::Vector2f IGameObject::getPosition() const {
    return this->m_position;
}

void IGameObject::setVelocity(const sf::Vector2f &velocity) {
    this->m_velocity = velocity;
}

sf::Vector2f IGameObject::getVelocity() const {
    return this->m_velocity;
}

void IGameObject::setAcceleration(const sf::Vector2f &acceleration) {
    this->m_acceleration = acceleration;
}

sf::Vector2f IGameObject::getAcceleration() const {
    return this->m_acceleration;
}

void IGameObject::updateSprites() {
    for (auto& entity : this->m_entities) {
        sf::Vector2f newPosition;
        newPosition.x = this->m_position.x + entity->getOffset().x;
        newPosition.y = this->m_position.y + entity->getOffset().y;
        entity->setPosition(newPosition);
    }
}

sf::IntRect IGameObject::getBoundingBox() const {
    return this->m_boundingBox;
}

void IGameObject::setBoundingBox(const sf::IntRect &boundingBox) {
    this->m_boundingBox = boundingBox;
}
