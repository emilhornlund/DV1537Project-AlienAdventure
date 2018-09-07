/**
 * @file ObjectHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "ObjectHandler.hpp"
#include "GameObject.hpp"
#include "Game.hpp"
#include "WindowHandler.hpp"

ObjectHandler::ObjectHandler(Game* game) {
    this->game = game;
}

ObjectHandler::~ObjectHandler() {
    this->clearObjects();
}

void ObjectHandler::clearObjects() {
    this->objects.clear();
}

void ObjectHandler::addObject(GameObject *object) {
    std::shared_ptr<GameObject> sharedPtr;
    sharedPtr.reset(object);
    this->objects.push_back(sharedPtr);
}

unsigned long ObjectHandler::getNumberOfObjects() const {
    return this->objects.size();
}

GameObject& ObjectHandler::getObject(const unsigned int index) const {
    return *this->objects[index];
}

void ObjectHandler::restoreObjects(const bool respawn) {
    for (const auto &object : this->objects) {
        object->restore(respawn);
    }
}

void ObjectHandler::updateObjects(const float dt) {
    for (const auto &object : this->objects) {
        object->processEvents();
        object->update(dt);
    }
}

void ObjectHandler::drawObjects() const {
    for (const auto &object : this->objects) {
        this->game->getWindowHandler()->draw(*object);
    }
}
