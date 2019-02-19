/**
 * @file Game.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Core/SceneHandler.hpp>

#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/SplashScene.hpp>

AA::Game::Game() : IGame(800, 600, "Alien Adventure") {
    auto splashScene = std::make_shared<SplashScene>(this);
    this->getSceneHandler().addActiveScene(splashScene);

    auto gameScene = std::make_shared<GameScene>(this, "Level1.tmx");
    this->getSceneHandler().addInactiveScene(gameScene);
}

AA::Game::~Game() = default;
