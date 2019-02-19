/**
 * @file Background.hpp
 * @date 2016-12-10
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_PARALLAXBACKGROUND_HPP
#define ALIENADVENTURE_PARALLAXBACKGROUND_HPP

#include <Core/IGameObject.hpp>

#include <memory>
#include <vector>

namespace CGL { //CoreGameLib
    class IGame;
    class SpriteEntity;
}

namespace AA { //AlienAdventure
    class ParallaxBackground : public CGL::IGameObject {
    private:
        std::vector<std::vector<std::shared_ptr<CGL::SpriteEntity>>> m_layers;

        sf::Vector2f m_lastCenter;

        void setupLayer(const unsigned int layer);

        ParallaxBackground(const ParallaxBackground &original);

        ParallaxBackground &operator=(const ParallaxBackground &original);
    public:
        explicit ParallaxBackground(CGL::IGame *game);

        ~ParallaxBackground() override;

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif /* ParallaxBackground_hpp */
