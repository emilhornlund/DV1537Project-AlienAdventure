//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/ObjectHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IScene.hpp>

CGL::IScene::IScene(IGame *game) : m_game(game), m_initialized(false), m_paused(false), m_elapsedTime(0), m_pausedTime(0) {
    this->m_objectHandler = std::make_shared<ObjectHandler>(game);
}

CGL::IScene::~IScene() = default;

CGL::IGame *CGL::IScene::getGame() const {
    return this->m_game;
}

void CGL::IScene::init() {
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

void CGL::IScene::deinit() {
    if (!this->m_initialized)
        return;

    this->m_initialized = false;

    this->m_elapsedTime += this->m_elapsedClock.getElapsedTime().asSeconds();

    if (this->m_paused) {
        this->m_pausedTime += this->m_pausedClock.getElapsedTime().asSeconds();
    }

    this->performDeinit();
}

CGL::ObjectHandler &CGL::IScene::getObjectHandler() const {
    return *this->m_objectHandler;
}

void CGL::IScene::processEvents() {
    this->processExtraEvents();
}

void CGL::IScene::update(const float dt) {
    this->m_objectHandler->updateObjects(dt);
    this->performExtraUpdates(dt);
}

void CGL::IScene::draw() {
    this->m_objectHandler->drawObjects();
    this->performExtraDrawing();
}

bool CGL::IScene::isInitialized() const {
    return this->m_initialized;
}

void CGL::IScene::pause() {
    if (this->m_paused)
        return;
    this->m_paused = true;
    this->m_pausedClock.restart();
}

void CGL::IScene::resume() {
    if (!this->m_paused)
        return;
    this->m_paused = false;
    this->m_pausedTime = this->m_pausedClock.getElapsedTime().asSeconds();
}

bool CGL::IScene::isPaused() const {
    return this->m_paused;
}

float CGL::IScene::getElapsedTime() const {
    auto result = this->m_initialized ? this->m_elapsedClock.getElapsedTime().asSeconds() : this->m_elapsedTime;
    return result;
}

float CGL::IScene::getPausedTime() const {
    return this->m_pausedTime;
}
