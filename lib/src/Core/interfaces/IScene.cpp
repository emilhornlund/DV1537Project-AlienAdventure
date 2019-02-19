//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "../../include/classes/ObjectHandler.hpp"
#include "../../include/interfaces/IGame.hpp"
#include "../../include/interfaces/IScene.hpp"

IScene::IScene(IGame *game) : m_game(game), m_initialized(false), m_paused(false), m_elapsedTime(0), m_pausedTime(0) {
    this->m_objectHandler = std::make_shared<ObjectHandler>(game);
}

IScene::~IScene() = default;

IGame *IScene::getGame() const {
    return this->m_game;
}

void IScene::init() {
    if (this->m_initialized)
        return;

    this->m_initialized = true;

    this->m_elapsedTime = 0;
    this->m_elapsedClock.restart();

    this->m_paused = false;
    this->m_pausedTime = 0;
    this->m_pausedClock.restart();

    this->performInit();
}

void IScene::deinit() {
    if (!this->m_initialized)
        return;

    this->m_initialized = false;

    this->m_elapsedTime += this->m_elapsedClock.getElapsedTime().asSeconds();

    if (this->m_paused) {
        this->m_pausedTime += this->m_pausedClock.getElapsedTime().asSeconds();
    }

    this->performDeinit();
}

ObjectHandler &IScene::getObjectHandler() const {
    return *this->m_objectHandler;
}

void IScene::processEvents() {
    this->processExtraEvents();
}

void IScene::update(const float dt) {
    this->m_objectHandler->updateObjects(dt);
    this->performExtraUpdates(dt);
}

void IScene::draw() {
    this->m_objectHandler->drawObjects();
    this->performExtraDrawing();
}

bool IScene::isInitialized() const {
    return this->m_initialized;
}

void IScene::pause() {
    if (this->m_paused)
        return;
    this->m_paused = true;
    this->m_pausedClock.restart();
}

void IScene::resume() {
    if (!this->m_paused)
        return;
    this->m_paused = false;
    this->m_pausedTime = this->m_pausedClock.getElapsedTime().asSeconds();
}

bool IScene::isPaused() const {
    return this->m_paused;
}

float IScene::getElapsedTime() const {
    auto result = this->m_initialized ? this->m_elapsedClock.getElapsedTime().asSeconds() : this->m_elapsedTime;
    return result;
}

float IScene::getPausedTime() const {
    return this->m_pausedTime;
}
