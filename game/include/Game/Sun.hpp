//
// Created by Emil Hörnlund on 2018-09-13.
//

#ifndef ALIENADVENTURE_SUN_HPP
#define ALIENADVENTURE_SUN_HPP

#include <Core/IGameObject.hpp>

#include <memory>
#include <vector>

namespace AA { //AlienAdventure
    class Sun : public CGL::IGameObject {
    private:
        Sun(const Sun &original);

        Sun &operator=(const Sun &original);
    public:
        explicit Sun(CGL::IGame *game);

        ~Sun() override;

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif //ALIENADVENTURE_SUN_HPP
