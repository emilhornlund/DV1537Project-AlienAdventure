//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/SceneHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IScene.hpp>

CGL::SceneHandler::SceneHandler(IGame *game) : m_game(game) {}

CGL::SceneHandler::~SceneHandler() = default;

bool CGL::SceneHandler::isEmpty() const {
    return this->m_scenes.empty();
}

void CGL::SceneHandler::addActiveScene(std::shared_ptr<IScene> scene) {
    if (!this->m_scenes.empty()) {
        this->m_scenes.back()->pause();
    }
    this->m_scenes.push_back(scene);
    this->m_scenes.back()->init();
}

void CGL::SceneHandler::addInactiveScene(std::shared_ptr<IScene> scene) {
    this->m_scenes.insert(this->m_scenes.begin(), scene);
}

CGL::IScene &CGL::SceneHandler::getActiveScene() const {
    return *this->m_scenes.back();
}

void CGL::SceneHandler::inactivateActivateScene() {
    if (!this->m_scenes.empty()) {
        auto scene = this->m_scenes.back();
        scene->pause();
        this->m_scenes.pop_back();
        this->m_scenes.insert(this->m_scenes.begin(), scene);
    } else {
        this->m_game->quit(0);
    }

    if (!this->m_scenes.empty()) {
        auto scene = this->m_scenes.back();
        if (scene->isInitialized()) {
            scene->resume();
        } else {
            scene->init();
        }
    } else {
        this->m_game->quit(0);
    }
}

void CGL::SceneHandler::dropActiveScene() {
    if (!this->m_scenes.empty()) {
        auto scene = this->m_scenes.back();
        scene->pause();
        scene->deinit();
        this->m_scenes.pop_back();
        this->m_deadScenes.push_back(scene);
    } else {
        this->m_game->quit(0);
    }

    if (!this->m_scenes.empty()) {
        auto scene = this->m_scenes.back();
        if (scene->isInitialized()) {
            scene->resume();
        } else {
            scene->init();
        }
    } else {
        this->m_game->quit(0);
    }
}

void CGL::SceneHandler::cleanup() {
    if (!this->m_deadScenes.empty()) {
        auto scene = this->m_deadScenes.back();
        this->m_deadScenes.pop_back();
        if (scene->isInitialized()) {
            scene->deinit();
        }
    }

    if (this->m_scenes.empty()) {
        this->m_game->quit(0);
    }
}
