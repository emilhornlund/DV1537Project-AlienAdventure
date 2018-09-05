/**
 * @file GameObject.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "AnimationFrame.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "StaticFrame.hpp"

GameObject::GameObject(Game* game) {
    this->game = game;

    this->animation = new AnimationHandler(game);
    this->depth = 0;
    this->visible = true;
}

GameObject::GameObject(const GameObject &original) {
    this->game = original.getGame();
    this->animation = original.animation->clone();
    this->depth = original.getDepth();
    this->visible = original.isVisible();
    this->position = original.getPosition();
    this->velocity = original.getVelocity();
    this->acceleration = original.getAcceleration();
    this->boundingBox = original.getBoundingBox();
}

GameObject& GameObject::operator=(const GameObject &original) {
    if (this != &original) {
        this->game = original.getGame();

        delete this->animation;
        this->animation = original.animation->clone();

        this->depth = original.getDepth();
        this->visible = original.isVisible();
        this->position = original.getPosition();
        this->velocity = original.getVelocity();
        this->acceleration = original.getAcceleration();
        this->boundingBox = original.getBoundingBox();
    }
    return *this;
}


GameObject::~GameObject() {
    delete this->animation;
    this->animation = nullptr;
}

Game* GameObject::getGame() const {
    return this->game;
}

int GameObject::getDepth() const {
    return this->depth;
}

void GameObject::setDepth(const int depth) {
    this->depth = depth;
}

bool GameObject::isVisible() const {
    return visible;
}

void GameObject::setVisible(const bool visible) {
    this->visible = visible;
}

void GameObject::setPosition(const sf::Vector2f &position) {
    this->position = position;
}

void GameObject::move(const sf::Vector2f &moveBy) {
    this->position += moveBy;
}

sf::Vector2f GameObject::getPosition() const {
    return this->position;
}

void GameObject::setVelocity(const sf::Vector2f &velocity) {
    this->velocity = velocity;
}

sf::Vector2f GameObject::getVelocity() const {
    return this->velocity;
}

void GameObject::setAcceleration(const sf::Vector2f &acceleration) {
    this->acceleration = acceleration;
}

sf::Vector2f GameObject::getAcceleration() const {
    return this->acceleration;
}

AnimationHandler* GameObject::getAnimationHandler() const {
    return this->animation;
}

void GameObject::updateSprites() {
    for (unsigned int i = 0; i < this->getAnimationHandler()->numberOfStaticFrames(); i++) {
        StaticFrame* frame = this->getAnimationHandler()->getStaticFrame(i);
        if (frame != nullptr) {
            sf::Vector2f tempPosition = this->getPosition();
            tempPosition.x += frame->getOffset().x;
            tempPosition.y += frame->getOffset().y;
            frame->setPosition(tempPosition);
        }
    }

    if (this->getAnimationHandler()->numberOfSequences() > 0) {
        AnimationSequence* sequence = this->animation->getCurrentSequence();
        if (sequence != nullptr) {
            AnimationFrame* frame = sequence->getCurrentFrame();
            if (frame != nullptr) {
                frame->setPosition(this->position);
            }
        }
    }
}

sf::IntRect GameObject::getBoundingBox() const {
    return this->boundingBox;
}

void GameObject::setBoundingBox(const sf::IntRect boundingBox) {
    this->boundingBox = boundingBox;
}
