//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_CLOUD_HPP
#define ALIENADVENTURE_CLOUD_HPP

#include <Core/IGameObject.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class IGame;
    class SpriteEntity;
}

namespace AA { //AlienAdventure
    class Cloud : public CGL::IGameObject {
    private:
        std::shared_ptr<CGL::SpriteEntity> m_entity;

        sf::IntRect m_spawnArea;

        float m_speed;

        Cloud(const Cloud &original);

        Cloud &operator=(const Cloud &original);

        int randomZIndex() const;

        float randomSpeed() const;
    public:
        explicit Cloud(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~Cloud() override;

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif //ALIENADVENTURE_CLOUD_HPP
