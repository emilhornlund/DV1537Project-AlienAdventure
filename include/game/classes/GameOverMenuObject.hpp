//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_GAMEOVERMENUOBJECT_HPP
#define ALIENADVENTURE_GAMEOVERMENUOBJECT_HPP

#include "core/interfaces/IMenuObject.hpp"

class GameOverMenuObject : public IMenuObject {
private:
    GameOverMenuObject(const GameOverMenuObject &original);

    GameOverMenuObject& operator=(const GameOverMenuObject &original);
public:
    explicit GameOverMenuObject(IGame *game);

    ~GameOverMenuObject() override;

    void update(const float dt) override;
};

#endif //ALIENADVENTURE_GAMEOVERMENUOBJECT_HPP
