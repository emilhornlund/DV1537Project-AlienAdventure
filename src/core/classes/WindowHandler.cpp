/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "core/classes/Camera.hpp"
#include "core/classes/Menu.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/WindowHandler.hpp"
#include "core/interfaces/IEntity.hpp"
#include "core/interfaces/IGame.hpp"
#include "core/interfaces/IGameObject.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

WindowHandler::WindowHandler(IGame* game, const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title) : m_game(game) {
    this->m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight, 32), title, sf::Style::Titlebar | sf::Style::Close);
    this->m_window->setKeyRepeatEnabled(true);
    this->m_window->setMouseCursorVisible(false);
    this->m_window->setVerticalSyncEnabled(true);

    this->m_icon = &this->getGame()->getImageResourceHandler().load("./resources/Icon.png");
    this->m_window->setIcon(this->m_icon->getSize().x, this->m_icon->getSize().y, this->m_icon->getPixelsPtr());

    this->m_camera = std::make_shared<Camera>(sf::FloatRect(0, 0, windowWidth, windowHeight));
    this->m_window->setView(this->m_camera->getView());
}

WindowHandler::~WindowHandler() = default;

IGame*  WindowHandler::getGame() const {
    return this->m_game;
}

void WindowHandler::addRenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera) {
    std::shared_ptr<RenderItem> item = std::make_shared<RenderItem>(drawable, depth, useCamera);
    this->m_renderItems.push_back(item);
}

void WindowHandler::sortQueue() {
    std::sort(this->m_renderItems.begin(), this->m_renderItems.end(), [](const std::shared_ptr<RenderItem> &lhs, const std::shared_ptr<RenderItem> &rhs) -> bool {
        return lhs->getDepth() > rhs->getDepth();
    });
};

sf::RenderWindow& WindowHandler::getRenderWindow() const {
    return *this->m_window;
}

Camera& WindowHandler::getCamera() const {
    return *this->m_camera;
}

void WindowHandler::render() {
    this->sortQueue();

    for (const auto& item : this->m_renderItems) {
        if (item->isUsingCamera()) {
            this->m_window->setView(this->m_camera->getView());
        } else {
            this->m_window->setView(this->m_window->getDefaultView());
        }
        this->m_window->draw(*item->getDrawable());
    }

    this->m_window->setView(this->m_window->getDefaultView());

    auto currentState = this->getGame()->getState();
    switch (currentState) {
        case IGame::GameState::Playing:
            break;
        case IGame::GameState::Paused:
            this->m_window->draw(this->m_game->getPauseMenu());
            break;
        case IGame::GameState::Respawn:
            this->m_window->draw(this->m_game->getRespawnMenu());
            break;
        case IGame::GameState::GameOver:
            this->m_window->draw(this->m_game->getGameOverMenu());
            break;
        case IGame::GameState::Uninitialized:
            throw std::runtime_error("Game is not yet initialized");
    }

    this->m_window->display();
    this->m_renderItems.clear();
}

void WindowHandler::clear(sf::Color color) {
    this->m_window->clear(color);
}

void WindowHandler::draw(IGameObject &object) {
    int updates = 0;
    for (unsigned long i = 0; i < object.getEntitiesSize(); i++) {
        auto* entity = &object.getEntity(i);
        this->addRenderItem(entity, (unsigned int) object.getZIndex(), object.isUsingCamera());
        updates++;
    }
    if (updates > 0) {
        object.updateSprites();
    }
}

WindowHandler::RenderItem::RenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera) {
    this->drawable = drawable;
    this->depth = depth;
    this->useCamera = useCamera;
}

WindowHandler::RenderItem::~RenderItem() = default;

unsigned int WindowHandler::RenderItem::getDepth() const {
    return this->depth;
}

sf::Drawable* WindowHandler::RenderItem::getDrawable() const {
    return this->drawable;
}

bool WindowHandler::RenderItem::isUsingCamera() const {
    return this->useCamera;
}
