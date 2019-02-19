/**
 * @file ObjectHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Core/classes/ObjectHandler.hpp>
#include <Core/classes/WindowHandler.hpp>
#include <Core/interfaces/IGame.hpp>
#include <Core/interfaces/IGameObject.hpp>

ObjectHandler::ObjectHandler(IGame* game) : m_game(game) {}

ObjectHandler::~ObjectHandler() {
    this->clearObjects();
}

void ObjectHandler::addObject(std::shared_ptr<IGameObject> object) {
    this->m_objects.push_back(object);
}

unsigned long ObjectHandler::getNumberOfObjects() const {
    return this->m_objects.size();
}

IGameObject& ObjectHandler::getObject(const unsigned int index) const {
    return *this->m_objects[index];
}

void ObjectHandler::clearObjects() {
    this->m_objects.clear();
}

void ObjectHandler::restoreObjects(const bool respawn) {
    for (const auto &object : this->m_objects) {
        object->restore(respawn);
    }
}

void ObjectHandler::updateObjects(const float dt) {
    for (const auto &object : this->m_objects) {
        object->processEvents();
        object->update(dt);
    }
}

void ObjectHandler::drawObjects() const {
    for (const auto &object : this->m_objects) {
        this->m_game->getWindowHandler().draw(*object);
    }
}
