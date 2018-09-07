/**
 * @file AnimationFrame.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef ANIMATION_FRAME_HPP
#define ANIMATION_FRAME_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class AnimationFrame : public sf::Sprite {
private:
    float duration;

    AnimationFrame(const AnimationFrame &original);

    AnimationFrame& operator=(const AnimationFrame &original);
public:
    explicit AnimationFrame(float duration = 0);

    ~AnimationFrame() override;

    void setDuration(const float duration);

    float getDuration() const;
};

#endif /* Frame_hpp */
