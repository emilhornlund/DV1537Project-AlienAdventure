/**
 * @file Game.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "EventHandler.hpp"
#include "Game.hpp"
#include "Hud.hpp"
#include "LevelHandler.hpp"
#include "Menu.hpp"
#include "ObjectHandler.hpp"
#include "WindowHandler.hpp"
#include "ResourceHandler.hpp"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

Game::Game() {
    //signal the game as not yet running.
    this->state = GameState::Uninitialized;
    this->running = false;
    this->exitCode = 0;

    //initialize resource handlers
    this->imageResourceHandler = new ImageResourceHandler;
    this->musicResourceHandler = new MusicResourceHandler;
    this->textureResourceHandler = new TextureResourceHandler;
    this->soundBufferResourceHandler = new SoundBufferResourceHandler;

    //initialize other handlers
    this->windowHandler = new WindowHandler(this, WINDOW_WIDTH, WINDOW_HEIGHT, "Alien Adventure");
    this->eventHandler = new EventHandler(*(this->windowHandler->getRenderWindow()));
    this->objectHandler = new ObjectHandler(this);
    this->levelHandler = new LevelHandler(this);

    //initialize the hud
    this->hud = new Hud(this);

    //initialize menus
    this->pauseMenu = new Menu(this, Menu::MenuType::Pause);
    this->respawnMenu = new Menu(this, Menu::MenuType::Respawn);
    this->gameOverMenu = new Menu(this, Menu::MenuType::GameOver);

    //position the menus
    this->pauseMenu->setPosition({(float)(WINDOW_WIDTH - this->pauseMenu->getSize().x)/2, (float)(WINDOW_HEIGHT - this->pauseMenu->getSize().y)/2});
    this->respawnMenu->setPosition({(float)(WINDOW_WIDTH - this->respawnMenu->getSize().x)/2, (float)(WINDOW_HEIGHT - this->respawnMenu->getSize().y)/2});
    this->gameOverMenu->setPosition({(float)(WINDOW_WIDTH - this->gameOverMenu->getSize().x)/2, (float)(WINDOW_HEIGHT - this->gameOverMenu->getSize().y)/2});

    //configure background music
    std::string rpath = "./resources/Music.ogg";
    this->musicResourceHandler->open(rpath);
    this->backgroundMusic = &this->musicResourceHandler->get(rpath);
    this->backgroundMusic->setLoop(true);
    this->backgroundMusic->setVolume(50);

    //configure menu click sound
    rpath = "./resources/Click.wav";
    this->soundBufferResourceHandler->load(rpath);
    this->clickSoundBuffer = &this->soundBufferResourceHandler->get(rpath);
    this->clickSound = new sf::Sound;
    this->clickSound->setBuffer(*this->clickSoundBuffer);
}

Game::~Game() {
    delete this->windowHandler;
    this->windowHandler = nullptr;

    delete this->eventHandler;
    this->eventHandler = nullptr;

    delete this->objectHandler;
    this->objectHandler = nullptr;

    delete this->levelHandler;
    this->levelHandler = nullptr;

    delete this->imageResourceHandler;
    this->imageResourceHandler = nullptr;

    delete this->musicResourceHandler;
    this->musicResourceHandler = nullptr;

    delete this->textureResourceHandler;
    this->textureResourceHandler = nullptr;

    delete this->soundBufferResourceHandler;
    this->soundBufferResourceHandler = nullptr;

    delete this->hud;
    this->hud = nullptr;

    delete this->pauseMenu;
    this->pauseMenu = nullptr;

    delete this->respawnMenu;
    this->respawnMenu = nullptr;

    delete this->gameOverMenu;
    this->gameOverMenu = nullptr;

    delete this->clickSound;
    this->clickSound = nullptr;
}

int Game::run() {
    this->backgroundMusic->play();

    this->levelHandler->load();
    this->objectHandler->restoreObjects(false);

    this->setState(GameState::Playing);

    this->exitCode = EXIT_SUCCESS;
    this->running = true;

    while (this->running && !this->getEventHandler()->getWindowStatus().closed) {
        this->update();
    }
    return this->exitCode;
}

void Game::update() {
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
                    this->hud->restore();
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
        this->objectHandler->updateObjects(delta.asSeconds());
    }

    this->draw();
}

void Game::draw() {
    this->windowHandler->clear(sf::Color(208, 244, 247));
    this->objectHandler->drawObjects();
    this->windowHandler->render();
}

bool Game::isRunning() const {
    return this->running;
}

void Game::quit(const int exitCode) {
    this->running = false;
    this->exitCode = exitCode;
}

void Game::setState(const GameState state) {
    this->state = state;
}

Game::GameState Game::getState() const {
    return this->state;
}

ImageResourceHandler *Game::getImageResourceHandler() const {
    return this->imageResourceHandler;
}

MusicResourceHandler *Game::getMusicResourceHandler() const {
    return this->musicResourceHandler;
}

TextureResourceHandler *Game::getTextureResourceHandler() const {
    return this->textureResourceHandler;
}

SoundBufferResourceHandler *Game::getSoundBufferResourceHandler() const {
    return this->soundBufferResourceHandler;
}

WindowHandler* Game::getRenderer() const {
    return this->windowHandler;
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
