//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_SPLASHOBJECT_HPP
#define ALIENADVENTURE_SPLASHOBJECT_HPP

#include <Core/IGameObject.hpp>

#include <vector>
#include <memory>

namespace AA { //AlienAdventure
    class SplashObject : public CGL::IGameObject {
    private:
        SplashObject(const SplashObject &original);

        SplashObject &operator=(const SplashObject &original);
    public:
        explicit SplashObject(CGL::IGame *game);

        ~SplashObject() override;

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif //ALIENADVENTURE_SPLASHOBJECT_HPP
