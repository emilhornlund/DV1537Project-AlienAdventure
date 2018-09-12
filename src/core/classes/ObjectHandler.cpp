/**
 * @file ObjectHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "core/classes/ObjectHandler.hpp"
#include "core/classes/WindowHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "core/interfaces/IGameObject.hpp"

ObjectHandler::ObjectHandler(IGame* game) : m_game(game) {}

ObjectHandler::~ObjectHandler() {
    this->clearObjects();
}

void ObjectHandler::addObject(IGameObject *object) {
    std::shared_ptr<IGameObject> sharedPtr;
    sharedPtr.reset(object);
    this->m_objects.push_back(sharedPtr);
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
