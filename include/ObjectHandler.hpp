/**
 * @file ObjectHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef OBJECT_HANDLER_HPP
#define OBJECT_HANDLER_HPP

#include "Core.hpp"

class ObjectHandler {
private:
    Game* game;

    unsigned int objectsCapacity;

    unsigned int objectsSize;

    GameObject** objects;

    void clearObjects();
public:
    explicit ObjectHandler(Game* game);

    ObjectHandler(const ObjectHandler &original);

    virtual ~ObjectHandler();

    virtual ObjectHandler& operator=(const ObjectHandler &original);

    void addObject(GameObject* object);

    int getNumberOfObjects() const;

    GameObject* getObject(const unsigned int index) const;

    void restoreObjects(const bool respawn = false);

    void updateObjects(const float delta);

    void drawObjects() const;
};

#endif /* ObjectManager_h */
