/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "AnimationFrame.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "LevelHandler.hpp"
#include "Menu.hpp"
#include "WindowHandler.hpp"
#include "StaticFrame.hpp"
#include "ResourceHandler.hpp"

#include <iostream>
#include <WindowHandler.hpp>

WindowHandler::RenderItem::RenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera) {
    this->drawable = drawable;
    this->depth = depth;
    this->useCamera = useCamera;
}

WindowHandler::RenderItem::RenderItem(const RenderItem &original) {
    this->drawable = original.drawable;
    this->depth = original.depth;
    this->useCamera = original.useCamera;
}

WindowHandler::RenderItem& WindowHandler::RenderItem::operator=(const WindowHandler::RenderItem &original) {
    if (this != &original) {
        this->drawable = original.getDrawable();
        this->depth = original.getDepth();
        this->useCamera = original.useCamera;
    }
    return *this;
}

WindowHandler::RenderItem::~RenderItem() = default;;

unsigned int WindowHandler::RenderItem::getDepth() const {
    return this->depth;
}

sf::Drawable* WindowHandler::RenderItem::getDrawable() const {
    return this->drawable;
}

bool WindowHandler::RenderItem::isUsingCamera() const {
    return this->useCamera;
}

bool WindowHandler::RenderItem::operator>(const RenderItem& original) const {
    return this->depth > original.depth;
}

bool WindowHandler::RenderItem::operator<(const RenderItem& original) const {
    return this->depth < original.depth;
}

WindowHandler::RenderItem* WindowHandler::RenderItem::clone() const {
    return new WindowHandler::RenderItem(*this);
}

WindowHandler::WindowHandler(Game *game, const unsigned int windowWidth, const unsigned int windowHeight,
                             const std::string &title) {
    this->game = game;

    this->queueCapacity = 0;
    this->queueSize = 0;
    this->queue = new RenderItem *[this->queueCapacity];

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight, 32), title, sf::Style::Titlebar | sf::Style::Close);
    window->setKeyRepeatEnabled(true);
    window->setMouseCursorVisible(false);
    window->setVerticalSyncEnabled(true);

    std::string rpath = "./resources/Icon.png";
    if (!this->getGame()->getImageResourceHandler()->isLoaded(rpath))
        this->getGame()->getImageResourceHandler()->load(rpath);
    this->icon = &this->game->getImageResourceHandler()->get(rpath);
    window->setIcon(this->icon->getSize().x, this->icon->getSize().y, this->icon->getPixelsPtr());

    this->camera = new Camera(sf::FloatRect(0, 0, windowWidth, windowHeight));
    window->setView(this->camera->getView());
    this->window = window;
}

WindowHandler::~WindowHandler() {
    this->clearQueue();

    delete this->window;
    this->window = nullptr;

    delete this->camera;
    this->camera = nullptr;
}

Game* WindowHandler::getGame() const {
    return this->game;
}

void WindowHandler::clearQueue() {
    for (int i = 0; i < this->queueSize; i++) {
        delete this->queue[i];
        this->queue[i] = nullptr;
    }
    delete[] this->queue;
    this->queue = nullptr;
}

void WindowHandler::addRenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera) {
    if (this->queueCapacity == this->queueSize) {
        this->queueCapacity += 5;
        auto **tempQueue = new RenderItem *[this->queueCapacity];
        for (int i = 0; i < this->queueSize; i++) {
            tempQueue[i] = this->queue[i]->clone();
        }
        this->clearQueue();
        this->queue = tempQueue;
    }
    this->queue[this->queueSize] = new RenderItem(drawable, depth, useCamera);
    this->queueSize++;
}

void WindowHandler::sortQueue() {
    int i, j, flag = 1;
    RenderItem* temp;
    for(i = 1; (i <= this->queueSize) && flag; i++) {
        flag = 0;
        for (j = 0; j < (this->queueSize - 1); j++) {
            if (*this->queue[j+1] > *this->queue[j]) {
                temp = this->queue[j];
                this->queue[j] = this->queue[j+1];
                this->queue[j+1] = temp;
                flag = 1;
            }
        }
    }
};

sf::RenderWindow* WindowHandler::getRenderWindow() {
    return this->window;
}

sf::View* WindowHandler::getView() {
    return &this->camera->getView();
}

Camera &WindowHandler::getCamera() const {
    return *this->camera;
}

void WindowHandler::render() {
    this->sortQueue();

    for (int i = 0; i < this->queueSize; i++) {
        auto &object = *queue[i];
        if (object.isUsingCamera()) {
            this->window->setView(this->camera->getView());
        } else {
            this->window->setView(this->window->getDefaultView());
        }
        this->window->draw(*object.getDrawable());
    }

    this->window->setView(this->window->getDefaultView());

    auto currentState = this->getGame()->getState();
    switch (currentState) {
        case Game::GameState::Playing:
            break;
        case Game::GameState::Paused:
            this->window->draw(*this->game->getPauseMenu());
            break;
        case Game::GameState::Respawn:
            this->window->draw(*this->game->getRespawnMenu());
            break;
        case Game::GameState::GameOver:
            this->window->draw(*this->game->getGameOverMenu());
            break;
        case Game::GameState::Uninitialized:
            throw std::runtime_error("Game is not yet initialized");
    }

    this->window->display();

    this->clearQueue();
    this->queueCapacity = 0;
    this->queueSize = 0;
}

void WindowHandler::clear(sf::Color color) {
    this->window->clear(color);
}

void WindowHandler::draw(GameObject &object) {
    AnimationHandler* animation = object.getAnimationHandler();
    if (animation != nullptr && object.isVisible()) {
        int updates = 0;
        if (animation->numberOfStaticFrames() > 0) {
            for (unsigned int i = 0; i < animation->numberOfStaticFrames(); i++) {
                StaticFrame* frame = animation->getStaticFrame(i);
                if (frame != nullptr) {
                    this->addRenderItem(frame, (unsigned int)object.getDepth(), object.isUsingCamera());
                    updates++;
                }
            }
        }
        AnimationSequence* sequence = animation->getCurrentSequence();
        if (sequence != nullptr) {
            AnimationFrame* frame = sequence->getCurrentFrame();
            if (frame != nullptr) {
                this->addRenderItem(frame, (unsigned int)object.getDepth(), object.isUsingCamera());
                updates++;
            }
        }
        if (updates > 0) {
            object.updateSprites();
        }
    }
}
