//
// Created by Emil Hörnlund on 2018-09-07.
//

#include <Core/Camera.hpp>
#include <Core/EventHandler.hpp>
#include <Core/Level.hpp>
#include <Core/ObjectHandler.hpp>
#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SceneHandler.hpp>
#include <Core/WindowHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IMenuObject.hpp>
#include <Core/IScene.hpp>
#include <Core/ConfigParser.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>

CGL::IGame::IGame(const std::string &title) {
    //initialize resource handlers
    this->m_imageResourceHandler = std::make_shared<ResourceHandler<sf::Image>>();
    this->m_musicResourceHandler = std::make_shared<ResourceHandler<sf::Music>>();
    this->m_soundBufferResourceHandler = std::make_shared<ResourceHandler<sf::SoundBuffer>>();
    this->m_textureResourceHandler = std::make_shared<ResourceHandler<sf::Texture>>();
    this->m_levelResourceHandler = std::make_shared<ResourceHandler<Level>>();

    //initialize and parse configs
    this->m_configParser = std::make_shared<ConfigParser>();
    if (!this->m_configParser->loadFromFile("defaults.cfg")) {
        throw std::runtime_error("Error opening config file");
    }

    //initialize other handlers
    this->m_propertyHandler = std::make_shared<PropertyHandler>();
    this->m_windowHandler = std::make_shared<WindowHandler>(this, title);
    this->m_eventHandler = std::make_shared<EventHandler>(this->m_windowHandler->getRenderWindow());
    this->m_sceneHandler = std::make_shared<SceneHandler>(this);

    //signal the include as not yet running.
    this->m_running = false;
    this->m_exitCode = 0;
}

CGL::IGame::~IGame() = default;

int CGL::IGame::run() {
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

bool CGL::IGame::isRunning() const {
    return this->m_running;
}

void CGL::IGame::quit(const int exitCode) {
    this->m_running = false;
    this->m_exitCode = exitCode;
}

void CGL::IGame::setMenu(std::shared_ptr<IMenuObject> menu) {
    this->m_menu = std::move(menu);
}

bool CGL::IGame::hasActiveMenu() const {
    return (this->m_menu != nullptr);
}

void CGL::IGame::closeMenu() {
    this->m_menu = nullptr;
}

CGL::PropertyHandler &CGL::IGame::getPropertyHandler() const {
    return *this->m_propertyHandler;
}

CGL::ResourceHandler<sf::Image> &CGL::IGame::getImageResourceHandler() const {
    return *this->m_imageResourceHandler;
}

CGL::ResourceHandler<sf::Music> &CGL::IGame::getMusicResourceHandler() const {
    return *this->m_musicResourceHandler;
}

CGL::ResourceHandler<sf::SoundBuffer>& CGL::IGame::getSoundBufferResourceHandler() const {
    return *this->m_soundBufferResourceHandler;
}

CGL::ResourceHandler<sf::Texture> &CGL::IGame::getTextureResourceHandler() const {
    return *this->m_textureResourceHandler;
}

CGL::ResourceHandler<CGL::Level> &CGL::IGame::getLevelResourceHandler() const {
    return *this->m_levelResourceHandler;
}

CGL::WindowHandler &CGL::IGame::getWindowHandler() const {
    return *this->m_windowHandler;
}

CGL::EventHandler &CGL::IGame::getEventHandler() const {
    return *this->m_eventHandler;
}

CGL::SceneHandler &CGL::IGame::getSceneHandler() const {
    return *this->m_sceneHandler;
}

CGL::ConfigParser &CGL::IGame::getConfigParser() const {
    return *this->m_configParser;
}
