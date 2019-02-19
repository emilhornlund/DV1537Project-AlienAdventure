/**
 * @file ObjectHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Core/ObjectHandler.hpp>
#include <Core/WindowHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IGameObject.hpp>

CGL::ObjectHandler::ObjectHandler(CGL::IGame* game) : m_game(game) {}

CGL::ObjectHandler::~ObjectHandler() {
    this->clearObjects();
}

void CGL::ObjectHandler::addObject(std::shared_ptr<IGameObject> object) {
    this->m_objects.push_back(object);
}

unsigned long CGL::ObjectHandler::getNumberOfObjects() const {
    return this->m_objects.size();
}

CGL::IGameObject& CGL::ObjectHandler::getObject(const unsigned int index) const {
    return *this->m_objects[index];
}

void CGL::ObjectHandler::clearObjects() {
    this->m_objects.clear();
}

void CGL::ObjectHandler::restoreObjects(const bool respawn) {
    for (const auto &object : this->m_objects) {
        object->restore(respawn);
    }
}

void CGL::ObjectHandler::updateObjects(const float dt) {
    for (const auto &object : this->m_objects) {
        object->processEvents();
        object->update(dt);
    }
}

void CGL::ObjectHandler::drawObjects() const {
    for (const auto &object : this->m_objects) {
        this->m_game->getWindowHandler().draw(*object);
    }
}
