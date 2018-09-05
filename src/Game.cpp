/**
 * @file Game.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "Game.hpp"
#include "Renderer.hpp"
#include "EventHandler.hpp"
#include "LevelHandler.hpp"
#include "ObjectHandler.hpp"
#include "Hud.hpp"
#include "Menu.hpp"

Game::Game() {
    this->running = true;
    this->render = new Renderer(this, {800, 600}, "Alien Adventure");
    this->eventHandler = new EventHandler(*(this->render->getRenderWindow()));
    this->objectHandler = new ObjectHandler(this);
    this->levelHandler = new LevelHandler(this);

    this->hud = new Hud;

    this->state = GameState::Playing;

    this->pauseMenu = new Menu(MenuType::Pause);
    this->pauseMenu->setPosition({(float)(800 - this->pauseMenu->getSize().x)/2, (float)(600 - this->pauseMenu->getSize().y)/2});

    this->respawnMenu = new Menu(MenuType::Respawn);
    this->respawnMenu->setPosition({(float)(800 - this->respawnMenu->getSize().x)/2, (float)(600 - this->respawnMenu->getSize().y)/2});

    this->gameOverMenu = new Menu(MenuType::GameOver);
    this->gameOverMenu->setPosition({(float)(800 - this->gameOverMenu->getSize().x)/2, (float)(600 - this->gameOverMenu->getSize().y)/2});

    std::string rpath = "./resources/Music.ogg";
    this->backgroundMusic = new sf::Music;
    if (!this->backgroundMusic->openFromFile(rpath)) {
        throw "Failed to load " + rpath;
    }
    this->backgroundMusic->setLoop(true);
    this->backgroundMusic->setVolume(50);
    this->backgroundMusic->play();

    rpath = "./resources/Click.wav";
    this->clickSoundBuffer = new sf::SoundBuffer;
    if (!this->clickSoundBuffer->loadFromFile(rpath)) {
        throw "Failed to load " + rpath;
    }
    this->clickSound = new sf::Sound;
    this->clickSound->setBuffer(*this->clickSoundBuffer);

    this->levelHandler->load();
    this->objectHandler->restoreObjects(0);
}

Game::~Game() {
    delete this->render;
    this->render = nullptr;

    delete this->eventHandler;
    this->eventHandler = nullptr;

    delete this->objectHandler;
    this->objectHandler = nullptr;

    delete this->levelHandler;
    this->levelHandler = nullptr;

    delete this->hud;
    this->hud = nullptr;

    delete this->pauseMenu;
    this->pauseMenu = nullptr;

    delete this->respawnMenu;
    this->respawnMenu = nullptr;

    delete this->gameOverMenu;
    this->gameOverMenu = nullptr;

    delete this->backgroundMusic;
    this->backgroundMusic = nullptr;

    delete this->clickSoundBuffer;
    this->clickSoundBuffer = nullptr;

    delete this->clickSound;
    this->clickSound = nullptr;
}

void Game::update() {
    this->eventHandler->updateEvents();

    if (this->eventHandler->getWindowStatus().lostFocus) {
        this->state = GameState::Paused;
    }

    switch (this->state) {
        case GameState::Playing:
            if (this->eventHandler->getKeyStatus(sf::Keyboard::Escape).pressed) {
                this->state = GameState::Paused;
            }
            break;
        case GameState::Paused:
            if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).pressed) {
                this->clickSound->play();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Return).released) {
                unsigned int index = this->pauseMenu->getSelection();
                if (index == 0) {
                    this->state = GameState::Playing;
                } else if (index == 1) {
                    this->state = GameState::Playing;
                    this->objectHandler->restoreObjects();
                } else {
                    this->running = false;
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
                    this->state = GameState::Playing;
                    this->objectHandler->restoreObjects(true);
                } else if (index == 1) {
                    this->state = GameState::Playing;
                    this->objectHandler->restoreObjects();
                } else {
                    this->running = false;
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
                    this->state = GameState::Playing;
                    this->hud->restore();
                    this->objectHandler->restoreObjects();
                } else {
                    this->running = false;
                }
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Down).pressed) {
                this->gameOverMenu->toggleNext();
            } else if (this->eventHandler->getKeyStatus(sf::Keyboard::Up).pressed) {
                this->gameOverMenu->togglePrevious();
            }
            break;
    }

    sf::Time delta = this->gameClock.restart();
    if (this->state != GameState::Paused) {
        this->objectHandler->updateObjects(delta.asSeconds());
    }

    this->draw();
}

void Game::draw() {
    this->render->clear(sf::Color(208, 244, 247));
    this->objectHandler->drawObjects();
    this->render->render();
}

bool Game::isRunning() const {
    return this->running;
}

void Game::setState(const GameState state) {
    this->state = state;
}

GameState Game::getState() const {
    return this->state;
}

Renderer* Game::getRenderer() const {
    return this->render;
}

EventHandler* Game::getEventHandler() const {
    return this->eventHandler;
}

ObjectHandler* Game::getObjectHandler() const {
    return this->objectHandler;
}

LevelHandler* Game::getLevelHandler() const {
    return this->levelHandler;
}

Hud* Game::getHud() const {
    return this->hud;
}

Menu* Game::getPauseMenu() const {
    return this->pauseMenu;
}

Menu* Game::getRespawnMenu() const {
    return this->respawnMenu;
}

Menu* Game::getGameOverMenu() const {
    return this->gameOverMenu;
}
