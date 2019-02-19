//
// Created by Emil Hörnlund on 2018-09-06.
//

#include <Core/classes/Camera.hpp>

#include <cmath>

const float MAX_VELOCITY_X = 100.0;
const float MAX_VELOCITY_Y = 100.0;

Camera::Camera(const sf::FloatRect &rect) : m_view(std::make_shared<sf::View>(rect)),
                                            m_bounds({0, 0, 0, 0}),
                                            m_minCenter({0, 0}),
                                            m_maxCenter({0, 0}),
                                            m_moving({0, 0}),
                                            m_targetPosition({0, 0}),
                                            m_acceleration({0, 0}),
                                            m_velocity({0, 0}) {}

Camera::~Camera() = default;

void Camera::setGlobalBounds(const sf::FloatRect &bounds) {
    this->m_bounds = bounds;

    this->m_minCenter.x = bounds.left + (this->getView().getSize().x / 2.0f);
    this->m_minCenter.y = 0;

    this->m_maxCenter.x = bounds.left + bounds.width - (this->getView().getSize().x / 2.0f);
    this->m_maxCenter.y = bounds.top + bounds.height - (this->getView().getSize().y / 2.0f);
}

sf::FloatRect Camera::getGlobalBounds() const {
    return this->m_bounds;
}

void Camera::setCenter(const sf::Vector2f &center, bool force) {
    sf::Vector2f newCenter = this->m_view->getCenter();
    if (force) {
        if (center.x < this->m_minCenter.x) {
            newCenter.x = this->m_minCenter.x;
        } else if (center.x > this->m_maxCenter.x) {
            newCenter.x = this->m_maxCenter.x;
        } else {
            newCenter.x = center.x;
        }
        if (center.y < this->m_minCenter.y) {
            newCenter.y = this->m_minCenter.y;
        } else if (center.y > this->m_maxCenter.y) {
            newCenter.y = this->m_maxCenter.y;
        } else {
            newCenter.y = center.y;
        }
    } else {
        if (this->m_view->getCenter().x != center.x) {
            if (center.x < this->m_minCenter.x) {
                this->m_targetPosition.x = this->m_minCenter.x;
            } else if (center.x > this->m_maxCenter.x) {
                this->m_targetPosition.x = this->m_maxCenter.x;
            } else {
                this->m_targetPosition.x = center.x;
            }

            float d = fabs(this->m_targetPosition.x - this->m_view->getCenter().x);
            if (d > 0) {
                this->m_moving.x = true;
                this->m_velocity.x = std::max(d * 2, MAX_VELOCITY_X);
            } else {
                this->m_moving.x = false;
                this->m_targetPosition.x = 0;
            }
        }
        if (this->m_view->getCenter().y != center.y) {
            if (center.y < this->m_minCenter.y) {
                this->m_targetPosition.y = this->m_minCenter.y;
            } else if (center.y > this->m_maxCenter.y) {
                this->m_targetPosition.y = this->m_maxCenter.y;
            } else {
                this->m_targetPosition.y = center.y;
            }

            float d = fabs(this->m_targetPosition.y - this->m_view->getCenter().y);
            if (d > 0) {
                this->m_moving.y = true;
                this->m_velocity.y = std::max(d * 2, MAX_VELOCITY_Y);
            } else {
                this->m_moving.y = false;
                this->m_targetPosition.y = 0;
            }
        }
    }
    this->m_view->setCenter(newCenter);
}

sf::Vector2f Camera::getCenter() const {
    return this->m_view->getCenter();
}

sf::View &Camera::getView() const {
    return *this->m_view;
}

void Camera::update(const double &dt) {
    sf::Vector2f newCenter = this->m_view->getCenter();

    if (this->m_moving.x) {
        if (this->m_view->getCenter().x < this->m_targetPosition.x) {
            newCenter.x += dt * this->m_velocity.x;
            if (newCenter.x > this->m_targetPosition.x) {
                newCenter.x = this->m_targetPosition.x;
                this->m_moving.x = false;
                this->m_targetPosition.x = 0;
                this->m_acceleration.x = 0;
                this->m_velocity.x = 0;
            }
        } else {
            newCenter.x -= dt * this->m_velocity.x;
            if (newCenter.x < this->m_targetPosition.x) {
                newCenter.x = this->m_targetPosition.x;
                this->m_moving.x = false;
                this->m_targetPosition.x = 0;
                this->m_acceleration.x = 0;
                this->m_velocity.x = 0;
            }
        }
    }

    if (this->m_moving.y) {
        if (this->m_view->getCenter().y < this->m_targetPosition.y) {
            newCenter.y += dt * this->m_velocity.y;
            if (newCenter.y > this->m_targetPosition.y) {
                newCenter.y = this->m_targetPosition.y;
                this->m_moving.y = false;
                this->m_targetPosition.y = 0;
                this->m_acceleration.y = 0;
                this->m_velocity.y = 0;
            }
        } else {
            newCenter.y -= dt * this->m_velocity.y;
            if (newCenter.y < this->m_targetPosition.y) {
                newCenter.y = this->m_targetPosition.y;
                this->m_moving.y = false;
                this->m_targetPosition.y = 0;
                this->m_acceleration.y = 0;
                this->m_velocity.y = 0;
            }
        }
    }

    this->m_view->setCenter(newCenter);
}
