//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_LEVELCOMPLETEMENUOBJECT_HPP
#define ALIENADVENTURE_LEVELCOMPLETEMENUOBJECT_HPP

#include <Core/IMenuObject.hpp>

namespace AA { //AlienAdventure
    class LevelCompleteMenuObject : public CGL::IMenuObject {
    private:
        LevelCompleteMenuObject(const LevelCompleteMenuObject &original);

        LevelCompleteMenuObject &operator=(const LevelCompleteMenuObject &original);
    public:
        explicit LevelCompleteMenuObject(CGL::IGame *game);

        ~LevelCompleteMenuObject() override;

        void update(const float dt) override;
    };
}

#endif //ALIENADVENTURE_LEVELCOMPLETEMENUOBJECT_HPP