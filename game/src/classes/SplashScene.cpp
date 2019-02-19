//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "core/classes/ObjectHandler.hpp"
#include "core/classes/SceneHandler.hpp"
#include "game/classes/Game.hpp"
#include "game/classes/SplashObject.hpp"
#include "game/classes/SplashScene.hpp"

#include <iostream>

SplashScene::SplashScene(IGame *game) : IScene(game) {
    auto obj = std::make_shared<SplashObject>(game);
    this->getObjectHandler().addObject(obj);
}

SplashScene::~SplashScene() = default;

void SplashScene::performInit() {

}

void SplashScene::performDeinit() {

}

void SplashScene::cleanup() {

}

void SplashScene::processExtraEvents() {

}

void SplashScene::performExtraUpdates(const float dt) {
    if (this->getElapsedTime() > 2) {
        this->getGame()->getSceneHandler().dropActiveScene();
    }
}

void SplashScene::performExtraDrawing() {

}

void SplashScene::didPause() {

}

void SplashScene::didResume() {

}
