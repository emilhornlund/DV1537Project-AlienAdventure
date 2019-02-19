//
// Created by Emil Hörnlund on 2018-09-06.
//

#ifndef COREGAMELIB_CAMERA_HPP
#define COREGAMELIB_CAMERA_HPP

#include <SFML/Graphics/View.hpp>

#include <memory>

namespace CGL { //CoreGameLib
    class Camera {
    private:
        std::shared_ptr<sf::View> m_view;

        sf::FloatRect m_bounds;

        sf::Vector2f m_minCenter;

        sf::Vector2f m_maxCenter;

        sf::Vector2i m_moving;

        sf::Vector2f m_targetPosition;

        sf::Vector2f m_acceleration;

        sf::Vector2f m_velocity;

        Camera(const Camera &original);

        Camera &operator=(const Camera &original);
    public:
        explicit Camera(const sf::FloatRect &rect);

        ~Camera();

        void setGlobalBounds(const sf::FloatRect &bounds);

        sf::FloatRect getGlobalBounds() const;

        void setCenter(const sf::Vector2f &center, bool force = false);

        sf::Vector2f getCenter() const;

        sf::View &getView() const;

        void update(const double &dt);
    };
}

#endif //COREGAMELIB_CAMERA_HPP
