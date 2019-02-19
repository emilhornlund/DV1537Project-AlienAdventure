//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_LEVELCOMPLETEMENUOBJECT_HPP
#define ALIENADVENTURE_LEVELCOMPLETEMENUOBJECT_HPP

#include "core/interfaces/IMenuObject.hpp"

class LevelCompleteMenuObject : public IMenuObject {
private:
    LevelCompleteMenuObject(const LevelCompleteMenuObject &original);

    LevelCompleteMenuObject& operator=(const LevelCompleteMenuObject &original);
public:
    explicit LevelCompleteMenuObject(IGame *game);

    ~LevelCompleteMenuObject() override;

    void update(const float dt) override;
};

#endif //ALIENADVENTURE_LEVELCOMPLETEMENUOBJECT_HPP
