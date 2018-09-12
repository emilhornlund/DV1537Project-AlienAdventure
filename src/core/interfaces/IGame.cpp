//
// Created by Emil Hörnlund on 2018-09-07.
//

#include "core/classes/Camera.hpp"
#include "core/classes/EventHandler.hpp"
#include "core/classes/Menu.hpp"
#include "core/classes/ObjectHandler.hpp"
#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/WindowHandler.hpp"
#include "core/interfaces/IGame.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>

IGame::IGame(const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title) {
    //initialize resource handlers
    this->imageResourceHandler = std::make_shared<ResourceHandler<sf::Image>>();
    this->musicResourceHandler = std::make_shared<ResourceHandler<sf::Music>>();
    this->soundBufferResourceHandler = std::make_shared<ResourceHandler<sf::SoundBuffer>>();
    this->textureResourceHandler = std::make_shared<ResourceHandler<sf::Texture>>();

    //initialize other handlers
    this->propertyHandler = std::make_shared<PropertyHandler>();
    this->windowHandler = std::make_shared<WindowHandler>(this, windowWidth, windowHeight, title);
    this->eventHandler = std::make_shared<EventHandler>(this->windowHandler->getRenderWindow());
    this->objectHandler = std::make_shared<ObjectHandler>(this);

    //signal the game as not yet running.
    this->state = GameState::Uninitialized;
    this->running = false;
    this->exitCode = 0;

    //initialize menus
    this->pauseMenu = std::make_shared<Menu>(this, Menu::MenuType::Pause);
    this->respawnMenu = std::make_shared<Menu>(this, Menu::MenuType::Respawn);
    this->gameOverMenu = std::make_shared<Menu>(this, Menu::MenuType::GameOver);

    //position the menus
    this->pauseMenu->setPosition({(float)(windowWidth - this->pauseMenu->getSize().x)/2, (float)(windowHeight - this->pauseMenu->getSize().y)/2});
    this->respawnMenu->setPosition({(float)(windowWidth - this->respawnMenu->getSize().x)/2, (float)(windowHeight - this->respawnMenu->getSize().y)/2});
    this->gameOverMenu->setPosition({(float)(windowWidth - this->gameOverMenu->getSize().x)/2, (float)(windowHeight - this->gameOverMenu->getSize().y)/2});

    //configure background music
    auto& rmusic = this->musicResourceHandler->open("./resources/Music.ogg");
    rmusic.setLoop(true);
    rmusic.setVolume(50);
    this->backgroundMusic = &rmusic;

    //configure menu click sound
    this->clickSound = std::make_shared<sf::Sound>();
    this->clickSound->setBuffer(this->soundBufferResourceHandler->load("./resources/Click.wav"));
}

IGame::~IGame() = default;

int IGame::run() {
    this->backgroundMusic->play();

    this->loadLevel();
    this->objectHandler->restoreObjects(false);

    this->setState(GameState::Playing);

    this->exitCode = EXIT_SUCCESS;
    this->running = true;

    while (this->running && !this->eventHandler->getWindowStatus().closed) {
        this->update();
    }

    return this->exitCode;
}

bool IGame::isRunning() const {
    return this->running;
}

void IGame::quit(const int exitCode) {
    this->running = false;
    this->exitCode = exitCode;
}

void IGame::setState(const IGame::GameState state) {
    this->state = state;
}

IGame::GameState IGame::getState() const {
    return this->state;
}

void IGame::update() {
    this->eventHandler->updateEvents();

    if (this->eventHandler->getWindowStatus().lostFocus) {
        this->setState(GameState::Paused);
    }

    switch (this->state) {
        case GameState::Playing:
            if (this->eventHandler->getKeyStatus(sf::Keyboard::Escape).pressed) {
                this->setState(GameState::Paused);
            }
            break;
        case GameState::Paused:
            if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).pressed) {
                this->clickSound->play();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).released) {
                unsigned int index = this->pauseMenu->getSelection();
                if (index == 0) {
                    this->setState(GameState::Playing);
                } else if (index == 1) {
                    this->setState(GameState::Playing);
                    this->objectHandler->restoreObjects(false);
                } else {
                    this->quit(EXIT_SUCCESS);
                }
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Down).pressed) {
                this->pauseMenu->toggleNext();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Up).pressed) {
                this->pauseMenu->togglePrevious();
            }
            break;
        case GameState::Respawn:
            if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).pressed) {
                this->clickSound->play();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).released) {
                unsigned int index = this->respawnMenu->getSelection();
                if (index == 0) {
                    this->setState(GameState::Playing);
                    this->objectHandler->restoreObjects(true);
                } else if (index == 1) {
                    this->setState(GameState::Playing);
                    this->objectHandler->restoreObjects(false);
                } else {
                    this->quit(EXIT_SUCCESS);
                }
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Down).pressed) {
                this->respawnMenu->toggleNext();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Up).pressed) {
                this->respawnMenu->togglePrevious();
            }
            break;
        case GameState::GameOver:
            if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).pressed) {
                this->clickSound->play();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).released) {
                unsigned int index = this->gameOverMenu->getSelection();
                if (index == 0) {
                    this->setState(GameState::Playing);
                    this->objectHandler->restoreObjects(false);
                } else {
                    this->quit(EXIT_SUCCESS);
                }
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Down).pressed) {
                this->gameOverMenu->toggleNext();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Up).pressed) {
                this->gameOverMenu->togglePrevious();
            }
            break;
        case GameState::Uninitialized:
            throw std::runtime_error("Game is not yet initialized");
    }

    sf::Time delta = this->gameClock.restart();
    if (this->state != GameState::Paused) {
        auto dt = delta.asSeconds();
        this->objectHandler->updateObjects(dt);
        this->windowHandler->getCamera().update(dt);
    }

    this->draw();
}

void IGame::draw() {
    this->windowHandler->clear(sf::Color(208, 244, 247));
    this->objectHandler->drawObjects();
    this->windowHandler->render();
}

PropertyHandler &IGame::getPropertyHandler() const {
    return *this->propertyHandler;
}

ResourceHandler<sf::Image> &IGame::getImageResourceHandler() const {
    return *this->imageResourceHandler;
}

ResourceHandler<sf::Music> &IGame::getMusicResourceHandler() const {
    return *this->musicResourceHandler;
}

ResourceHandler<sf::SoundBuffer>& IGame::getSoundBufferResourceHandler() const {
    return *this->soundBufferResourceHandler;
}

ResourceHandler<sf::Texture> &IGame::getTextureResourceHandler() const {
    return *this->textureResourceHandler;
}

WindowHandler &IGame::getWindowHandler() const {
    return *this->windowHandler;
}

EventHandler &IGame::getEventHandler() const {
    return *this->eventHandler;
}

ObjectHandler &IGame::getObjectHandler() const {
    return *this->objectHandler;
}

Menu &IGame::getPauseMenu() const {
    return *this->pauseMenu;
}

Menu &IGame::getRespawnMenu() const {
    return *this->respawnMenu;
}

Menu &IGame::getGameOverMenu() const {
    return *gameOverMenu;
}
