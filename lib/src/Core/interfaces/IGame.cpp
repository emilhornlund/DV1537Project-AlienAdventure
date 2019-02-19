//
// Created by Emil Hörnlund on 2018-09-07.
//

#include <Core/classes/Camera.hpp>
#include <Core/classes/EventHandler.hpp>
#include <Core/classes/Level.hpp>
#include <Core/classes/ObjectHandler.hpp>
#include <Core/classes/PropertyHandler.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/classes/SceneHandler.hpp>
#include <Core/classes/WindowHandler.hpp>
#include <Core/interfaces/IGame.hpp>
#include <Core/interfaces/IMenuObject.hpp>
#include <Core/interfaces/IScene.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>

IGame::IGame(const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title) {
    //initialize resource handlers
    this->m_imageResourceHandler = std::make_shared<ResourceHandler<sf::Image>>();
    this->m_musicResourceHandler = std::make_shared<ResourceHandler<sf::Music>>();
    this->m_soundBufferResourceHandler = std::make_shared<ResourceHandler<sf::SoundBuffer>>();
    this->m_textureResourceHandler = std::make_shared<ResourceHandler<sf::Texture>>();
    this->m_levelResourceHandler = std::make_shared<ResourceHandler<Level>>();

    //initialize other handlers
    this->m_propertyHandler = std::make_shared<PropertyHandler>();
    this->m_windowHandler = std::make_shared<WindowHandler>(this, windowWidth, windowHeight, title);
    this->m_eventHandler = std::make_shared<EventHandler>(this->m_windowHandler->getRenderWindow());
    this->m_sceneHandler = std::make_shared<SceneHandler>(this);

    //signal the include as not yet running.
    this->m_running = false;
    this->m_exitCode = 0;
}

IGame::~IGame() = default;

int IGame::run() {
    this->m_exitCode = EXIT_SUCCESS;
    this->m_running = true;

    while (this->m_running && !this->m_eventHandler->getWindowStatus().closed) {
        if (!this->m_sceneHandler->isEmpty()) {
            auto& scene = this->m_sceneHandler->getActiveScene();

            this->m_eventHandler->updateEvents();
            scene.processEvents();
            if (this->m_menu != nullptr) {
                this->m_menu->processEvents();
            }

            sf::Time delta = this->m_gameClock.restart();
            auto dt = delta.asSeconds();
            if (!scene.isPaused()) {
                scene.update(dt);
                this->m_windowHandler->getCamera().update(dt);
            }
            if (this->m_menu != nullptr) {
                this->m_menu->update(dt);
            }

            this->m_windowHandler->clear(sf::Color(208, 244, 247));
            scene.draw();
            if (this->m_menu != nullptr) {
                this->m_windowHandler->draw(*this->m_menu);
            }
            this->m_windowHandler->render();

            this->m_sceneHandler->cleanup();
        } else {
            this->quit(0);
        }
    }

    return this->m_exitCode;
}

bool IGame::isRunning() const {
    return this->m_running;
}

void IGame::quit(const int exitCode) {
    this->m_running = false;
    this->m_exitCode = exitCode;
}

void IGame::setMenu(std::shared_ptr<IMenuObject> menu) {
    this->m_menu = std::move(menu);
}

bool IGame::hasActiveMenu() const {
    return (this->m_menu != nullptr);
}

void IGame::closeMenu() {
    this->m_menu = nullptr;
}

PropertyHandler &IGame::getPropertyHandler() const {
    return *this->m_propertyHandler;
}

ResourceHandler<sf::Image> &IGame::getImageResourceHandler() const {
    return *this->m_imageResourceHandler;
}

ResourceHandler<sf::Music> &IGame::getMusicResourceHandler() const {
    return *this->m_musicResourceHandler;
}

ResourceHandler<sf::SoundBuffer>& IGame::getSoundBufferResourceHandler() const {
    return *this->m_soundBufferResourceHandler;
}

ResourceHandler<sf::Texture> &IGame::getTextureResourceHandler() const {
    return *this->m_textureResourceHandler;
}

ResourceHandler<Level> &IGame::getLevelResourceHandler() const {
    return *this->m_levelResourceHandler;
}

WindowHandler &IGame::getWindowHandler() const {
    return *this->m_windowHandler;
}

EventHandler &IGame::getEventHandler() const {
    return *this->m_eventHandler;
}

SceneHandler &IGame::getSceneHandler() const {
    return *this->m_sceneHandler;
}
