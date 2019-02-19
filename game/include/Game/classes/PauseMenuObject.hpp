//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_PAUSEMENUOBJECT_HPP
#define ALIENADVENTURE_PAUSEMENUOBJECT_HPP

#include <Core/interfaces/IMenuObject.hpp>

class PauseMenuObject : public IMenuObject {
private:
    PauseMenuObject(const PauseMenuObject &original);

    PauseMenuObject& operator=(const PauseMenuObject &original);
public:
    explicit PauseMenuObject(IGame *game);

    ~PauseMenuObject() override;

    void update(const float dt) override;
};

#endif //ALIENADVENTURE_PAUSEMENUOBJECT_HPP