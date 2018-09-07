/**
 * @file ObjectHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef OBJECT_HANDLER_HPP
#define OBJECT_HANDLER_HPP

#include <memory>
#include <vector>

#include "Core.hpp"

class ObjectHandler {
private:
    Game* game;

    std::vector<std::shared_ptr<GameObject>> objects;

    ObjectHandler(const ObjectHandler &original);

    ObjectHandler& operator=(const ObjectHandler &original);

    void clearObjects();
public:
    explicit ObjectHandler(Game* game);

    virtual ~ObjectHandler();

    void addObject(GameObject* object);

    unsigned long getNumberOfObjects() const;

    GameObject& getObject(const unsigned int index) const;

    void restoreObjects(const bool respawn = false);

    void updateObjects(const float dt);

    void drawObjects() const;
};

#endif /* ObjectManager_h */
