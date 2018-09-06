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

    this->objectsCapacity = 0;//50;
    this->objectsSize = 0;
    this->objects = new GameObject *[this->objectsCapacity];
}

ObjectHandler::ObjectHandler(const ObjectHandler &original) {
    this->game = original.game;

    this->objectsCapacity = original.objectsCapacity;
    this->objectsSize = original.objectsSize;

    this->objects = new GameObject *[this->objectsCapacity];
    for (int i = 0; i < this->objectsSize; i++) {
        this->objects[i] = original.objects[i]->clone();
    }
}

ObjectHandler::~ObjectHandler() {
    this->clearObjects();
}

ObjectHandler& ObjectHandler::operator=(const ObjectHandler &original) {
    if (this != &original) {
        this->game = original.game;

        this->clearObjects();
        this->objectsCapacity = original.objectsCapacity;
        this->objectsSize = original.objectsSize;

        this->objects = new GameObject *[this->objectsCapacity];
        for (int i = 0; i < this->objectsSize; i++) {
            this->objects[i] = original.objects[i]->clone();
        }
    }
    return *this;
}

void ObjectHandler::clearObjects() {
    for (int i = 0; i < this->objectsSize; i++) {
        delete this->objects[i];
        this->objects[i] = nullptr;
    }
    delete[] this->objects;
    this->objects = nullptr;
}

void ObjectHandler::addObject(GameObject *object) {
    if (this->objectsCapacity == this->objectsSize) {
        this->objectsCapacity += 5;
        auto **tempObjects = new GameObject *[this->objectsCapacity];
        for (int i = 0; i < this->objectsSize; i++) {
            tempObjects[i] = this->objects[i]->clone();
        }
        this->clearObjects();
        this->objects = tempObjects;
    }
    this->objects[this->objectsSize] = object;
    this->objectsSize++;
}

int ObjectHandler::getNumberOfObjects() const {
    return this->objectsSize;
}

GameObject* ObjectHandler::getObject(const unsigned int index) const {
    return this->objects[index];
}

void ObjectHandler::restoreObjects(const bool respawn) {
    for (int i = 0; i < this->objectsSize; i++) {
        this->objects[i]->restore(respawn);
    }
}

void ObjectHandler::updateObjects(const float delta) {
    for (int i = 0; i < this->objectsSize; i++) {
        this->objects[i]->processEvents();
        this->objects[i]->update(delta);
    }
}

void ObjectHandler::drawObjects() const {
    for (int i = 0; i < this->objectsSize; i++) {
        this->game->getRenderer()->draw(*this->objects[i]);
    }
}
