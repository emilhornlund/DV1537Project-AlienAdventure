/**
 * @file ObjectHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef OBJECT_HANDLER_HPP
#define OBJECT_HANDLER_HPP

#include <memory>
#include <vector>

class IGame;
class IGameObject;

class ObjectHandler {
private:
    IGame* m_game;

    std::vector<std::shared_ptr<IGameObject>> m_objects;

    ObjectHandler(const ObjectHandler &original);

    ObjectHandler& operator=(const ObjectHandler &original);
public:
    explicit ObjectHandler(IGame* game);

    virtual ~ObjectHandler();

    void addObject(std::shared_ptr<IGameObject> object);

    unsigned long getNumberOfObjects() const;

    IGameObject& getObject(const unsigned int index) const;

    void clearObjects();

    void restoreObjects(const bool respawn = false);

    void updateObjects(const float dt);

    void drawObjects() const;
};

#endif /* ObjectManager_h */
