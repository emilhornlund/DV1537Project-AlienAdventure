//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_GAMEOVERMENUOBJECT_HPP
#define ALIENADVENTURE_GAMEOVERMENUOBJECT_HPP

#include <Core/IMenuObject.hpp>

namespace AA { //AlienAdventure
    class GameOverMenuObject : public CGL::IMenuObject {
    private:
        GameOverMenuObject(const GameOverMenuObject &original);

        GameOverMenuObject &operator=(const GameOverMenuObject &original);
    public:
        explicit GameOverMenuObject(CGL::IGame *game);

        ~GameOverMenuObject() override;

        void update(const float dt) override;
    };
}

#endif //ALIENADVENTURE_GAMEOVERMENUOBJECT_HPP