/**
 * @file GameObject.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Core/IEntity.hpp>
#include <Core/IGame.hpp>
#include <Core/IGameObject.hpp>

#include <SFML/Graphics/Sprite.hpp>

CGL::IGameObject::IGameObject(IGame *game, const int zIndex, const bool useCamera) : m_game(game),
                                                                                      m_zIndex(zIndex),
                                                                                      m_visible(true),
                                                                                      m_useCamera(useCamera),
                                                                                      m_position(sf::Vector2f(0,0)),
                                                                                      m_velocity(sf::Vector2f(0,0)),
                                                                                      m_acceleration(sf::Vector2f(0,0)),
                                                                                      m_boundingBox(sf::IntRect(0,0,0,0)) {

}

CGL::IGameObject::~IGameObject() = default;

CGL::IGame* CGL::IGameObject::getGame() const {
    return this->m_game;
}

void CGL::IGameObject::addEntity(std::shared_ptr<CGL::IEntity> entity) {
    this->m_entities.push_back(entity);
}

unsigned long CGL::IGameObject::getEntitiesSize() const {
    return this->m_entities.size();
}

CGL::IEntity& CGL::IGameObject::getEntity(unsigned long index) const {
    return *this->m_entities.at(index);
}

void CGL::IGameObject::clearEntities() {
    this->m_entities.clear();
}

int CGL::IGameObject::getZIndex() const {
    return this->m_zIndex;
}

void CGL::IGameObject::setZIndex(const int depth) {
    this->m_zIndex = depth;
}

bool CGL::IGameObject::isVisible() const {
    return m_visible;
}

void CGL::IGameObject::setVisible(const bool visible) {
    this->m_visible = visible;
}

bool CGL::IGameObject::isUsingCamera() const {
    return this->m_useCamera;
}

void CGL::IGameObject::setPosition(const sf::Vector2f &position) {
    this->m_position = position;
}

void CGL::IGameObject::move(const sf::Vector2f &moveBy) {
    this->m_position += moveBy;
}

sf::Vector2f CGL::IGameObject::getPosition() const {
    return this->m_position;
}

void CGL::IGameObject::setVelocity(const sf::Vector2f &velocity) {
    this->m_velocity = velocity;
}

sf::Vector2f CGL::IGameObject::getVelocity() const {
    return this->m_velocity;
}

void CGL::IGameObject::setAcceleration(const sf::Vector2f &acceleration) {
    this->m_acceleration = acceleration;
}

sf::Vector2f CGL::IGameObject::getAcceleration() const {
    return this->m_acceleration;
}

void CGL::IGameObject::updateSprites() {
    for (auto& entity : this->m_entities) {
        sf::Vector2f newPosition;
        newPosition.x = this->m_position.x + entity->getOffset().x;
        newPosition.y = this->m_position.y + entity->getOffset().y;
        entity->setPosition(newPosition);
    }
}

sf::IntRect CGL::IGameObject::getBoundingBox() const {
    return this->m_boundingBox;
}

void CGL::IGameObject::setBoundingBox(const sf::IntRect &boundingBox) {
    this->m_boundingBox = boundingBox;
}
