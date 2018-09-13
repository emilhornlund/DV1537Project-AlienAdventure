/**
 * @file Background.hpp
 * @date 2016-12-10
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_PARALLAXBACKGROUND_HPP
#define ALIENADVENTURE_PARALLAXBACKGROUND_HPP

#include "core/interfaces/IGameObject.hpp"

#include <SFML/Graphics/VertexArray.hpp>

#include <memory>
#include <vector>

class IGame;
class SpriteEntity;

class ParallaxBackground : public IGameObject {
private:
    std::vector<std::vector<std::shared_ptr<SpriteEntity>>> m_layers;

    sf::Vector2f m_lastCenter;

    void setupLayer(const unsigned int layer);

    ParallaxBackground(const ParallaxBackground &original);

    ParallaxBackground& operator=(const ParallaxBackground &original);
public:
    explicit ParallaxBackground(IGame *game);

    ~ParallaxBackground() override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif /* ParallaxBackground_hpp */
