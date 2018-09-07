//
// Created by Emil Hörnlund on 2018-09-06.
//

#ifndef ALIENADVENTURE_CAMERA_HPP
#define ALIENADVENTURE_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class Camera {
private:
    sf::View *view;

    sf::FloatRect bounds;

    sf::Vector2f minCenter;

    sf::Vector2f maxCenter;

    sf::Vector2i moving;

    sf::Vector2f targetPosition;

    sf::Vector2f acceleration;

    sf::Vector2f velocity;

    Camera(const Camera &original);

    Camera& operator=(const Camera &original);
public:
    explicit Camera(const sf::FloatRect &rect);

    ~Camera();

    void setGlobalBounds(const sf::FloatRect& bounds);

    sf::FloatRect getGlobalBounds() const;

    void setCenter(const sf::Vector2f &center, bool force = false);

    sf::Vector2f getCenter() const;

    sf::View& getView() const;

    void update(const double& dt);
};

#endif //ALIENADVENTURE_CAMERA_HPP
