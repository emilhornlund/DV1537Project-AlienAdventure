//
// Created by Emil Hörnlund on 2018-09-07.
//

#ifndef ALIENADVENTURE_ANIMATEDENTITY_HPP
#define ALIENADVENTURE_ANIMATEDENTITY_HPP

#include "core/interfaces/IEntity.hpp"

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Time.hpp>

class Animation;

class AnimatedEntity : public IEntity {
private:
    const Animation* m_animation;

    sf::Time m_currentTime;

    std::size_t m_currentFrame;

    bool m_isPaused;

    sf::Vertex m_vertices[4];

    AnimatedEntity(const AnimatedEntity &original);

    AnimatedEntity& operator=(const AnimatedEntity &original);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    explicit AnimatedEntity(const bool paused = false);

    ~AnimatedEntity() override;

    void setAnimation(const Animation& animation);

    void play();

    void play(const Animation& animation);

    void pause();

    void stop();

    const Animation* getAnimation() const;

    const sf::FloatRect getLocalBounds() const;

    const sf::FloatRect getGlobalBounds() const;

    bool isPlaying() const;

    void setFrame(std::size_t newFrame, bool resetTime = true);

    void update(sf::Time deltaTime);

    void setColor(const sf::Color& color) override;
};

#endif //ALIENADVENTURE_ANIMATEDENTITY_HPP
