//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/ObjectHandler.hpp>
#include <Core/SceneHandler.hpp>

#include <Game/Game.hpp>
#include <Game/SplashObject.hpp>
#include <Game/SplashScene.hpp>

#include <iostream>

AA::SplashScene::SplashScene(CGL::IGame *game) : CGL::IScene(game) {
    auto obj = std::make_shared<SplashObject>(game);
    this->getObjectHandler().addObject(obj);
}

AA::SplashScene::~SplashScene() = default;

void AA::SplashScene::performInit() {

}

void AA::SplashScene::performDeinit() {

}

void AA::SplashScene::cleanup() {

}

void AA::SplashScene::processExtraEvents() {

}

void AA::SplashScene::performExtraUpdates(const float dt) {
    if (this->getElapsedTime() > 2) {
        this->getGame()->getSceneHandler().dropActiveScene();
    }
}

void AA::SplashScene::performExtraDrawing() {

}

void AA::SplashScene::didPause() {

}

void AA::SplashScene::didResume() {

}
