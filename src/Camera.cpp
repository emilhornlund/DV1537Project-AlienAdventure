//
// Created by Emil Hörnlund on 2018-09-06.
//

#include <cmath>

#include "Camera.hpp"

const float MAX_VELOCITY_X = 100.0;
const float MAX_VELOCITY_Y = 100.0;

Camera::Camera(const sf::FloatRect &rect) {
    this->view = new sf::View(rect);

    this->moving = {0, 0};
    this->targetPosition = {0, 0};
    this->acceleration = {0, 0};
    this->velocity = {0, 0};
}

Camera::~Camera() {
    delete this->view;
    this->view = nullptr;
}

void Camera::setGlobalBounds(const sf::FloatRect &bounds) {
    this->bounds = bounds;

    this->minCenter.x = bounds.left + (this->getView().getSize().x / 2.0f);
    this->minCenter.y = 0;

    this->maxCenter.x = bounds.left + bounds.width - (this->getView().getSize().x / 2.0f);
    this->maxCenter.y = bounds.top + bounds.height - (this->getView().getSize().y / 2.0f);
}

sf::FloatRect Camera::getGlobalBounds() const {
    return this->bounds;
}

void Camera::setCenter(const sf::Vector2f &center, bool force) {
    sf::Vector2f newCenter = this->view->getCenter();
    if (force) {
        if (center.x < this->minCenter.x) {
            newCenter.x = this->minCenter.x;
        } else if (center.x > this->maxCenter.x) {
            newCenter.x = this->maxCenter.x;
        } else {
            newCenter.x = center.x;
        }
        if (center.y < this->minCenter.y) {
            newCenter.y = this->minCenter.y;
        } else if (center.y > this->maxCenter.y) {
            newCenter.y = this->maxCenter.y;
        } else {
            newCenter.y = center.y;
        }
    } else {
        if (this->view->getCenter().x != center.x) {
            if (center.x < this->minCenter.x) {
                this->targetPosition.x = this->minCenter.x;
            } else if (center.x > this->maxCenter.x) {
                this->targetPosition.x = this->maxCenter.x;
            } else {
                this->targetPosition.x = center.x;
            }

            float d = fabs(this->targetPosition.x - this->view->getCenter().x);
            if (d > 0) {
                this->moving.x = true;
                this->velocity.x = std::max(d * 2, MAX_VELOCITY_X);
            } else {
                this->moving.x = false;
                this->targetPosition.x = 0;
            }
        }
        if (this->view->getCenter().y != center.y) {
            if (center.y < this->minCenter.y) {
                this->targetPosition.y = this->minCenter.y;
            } else if (center.y > this->maxCenter.y) {
                this->targetPosition.y = this->maxCenter.y;
            } else {
                this->targetPosition.y = center.y;
            }

            float d = fabs(this->targetPosition.y - this->view->getCenter().y);
            if (d > 0) {
                this->moving.y = true;
                this->velocity.y = std::max(d * 2, MAX_VELOCITY_Y);
            } else {
                this->moving.y = false;
                this->targetPosition.y = 0;
            }
        }
    }
    this->view->setCenter(newCenter);
}

sf::Vector2f Camera::getCenter() const {
    return this->view->getCenter();
}

sf::View &Camera::getView() const {
    return *this->view;
}

void Camera::update(const double &dt) {
    sf::Vector2f newCenter = this->view->getCenter();

    if (this->moving.x) {
        if (this->view->getCenter().x < this->targetPosition.x) {
            newCenter.x += dt * this->velocity.x;
            if (newCenter.x > this->targetPosition.x) {
                newCenter.x = this->targetPosition.x;
                this->moving.x = false;
                this->targetPosition.x = 0;
                this->acceleration.x = 0;
                this->velocity.x = 0;
            }
        } else {
            newCenter.x -= dt * this->velocity.x;
            if (newCenter.x < this->targetPosition.x) {
                newCenter.x = this->targetPosition.x;
                this->moving.x = false;
                this->targetPosition.x = 0;
                this->acceleration.x = 0;
                this->velocity.x = 0;
            }
        }
    }

    if (this->moving.y) {
        if (this->view->getCenter().y < this->targetPosition.y) {
            newCenter.y += dt * this->velocity.y;
            if (newCenter.y > this->targetPosition.y) {
                newCenter.y = this->targetPosition.y;
                this->moving.y = false;
                this->targetPosition.y = 0;
                this->acceleration.y = 0;
                this->velocity.y = 0;
            }
        } else {
            newCenter.y -= dt * this->velocity.y;
            if (newCenter.y < this->targetPosition.y) {
                newCenter.y = this->targetPosition.y;
                this->moving.y = false;
                this->targetPosition.y = 0;
                this->acceleration.y = 0;
                this->velocity.y = 0;
            }
        }
    }

    this->view->setCenter(newCenter);
}
