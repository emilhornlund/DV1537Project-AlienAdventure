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
public:
    explicit AnimationFrame(float duration = 0);

    AnimationFrame(const AnimationFrame &original);

    ~AnimationFrame() override;

    virtual AnimationFrame& operator=(const AnimationFrame &original);

    virtual AnimationFrame* clone() const;

    void setDuration(const float duration);

    float getDuration() const;
};

#endif /* Frame_hpp */
