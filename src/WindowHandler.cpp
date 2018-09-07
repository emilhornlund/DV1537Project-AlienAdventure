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
#include <algorithm>

WindowHandler::WindowHandler(Game *game, const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title) {
    this->game = game;

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
    delete this->window;
    this->window = nullptr;

    delete this->camera;
    this->camera = nullptr;
}

Game* WindowHandler::getGame() const {
    return this->game;
}

void WindowHandler::addRenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera) {
    std::shared_ptr<RenderItem> item = std::make_shared<RenderItem>(drawable, depth, useCamera);
    this->renderItems.push_back(item);
}

void WindowHandler::sortQueue() {
//    std::sort(this->renderItems.begin(), this->renderItems.end());
    //TODO: Implement a sort function here
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

    for (const auto& item : this->renderItems) {
        if (item->isUsingCamera()) {
            this->window->setView(this->camera->getView());
        } else {
            this->window->setView(this->window->getDefaultView());
        }
        this->window->draw(*item->getDrawable());
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
    this->renderItems.clear();
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
                auto *frame = &animation->getStaticFrame(i);
                if (frame != nullptr) {
                    this->addRenderItem(frame, (unsigned int)object.getDepth(), object.isUsingCamera());
                    updates++;
                }
            }
        }

        if (animation->numberOfSequences() > 0) {
            auto *sequence = &animation->getCurrentSequence();
            if (sequence != nullptr) {
                auto *frame = &sequence->getCurrentFrame();
                if (frame != nullptr) {
                    this->addRenderItem(frame, (unsigned int)object.getDepth(), object.isUsingCamera());
                    updates++;
                }
            }
        }

        if (updates > 0) {
            object.updateSprites();
        }
    }
}

WindowHandler::RenderItem::RenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera) {
    this->drawable = drawable;
    this->depth = depth;
    this->useCamera = useCamera;
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
