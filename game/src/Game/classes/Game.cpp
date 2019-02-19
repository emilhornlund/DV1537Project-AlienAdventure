/**
 * @file Game.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "../../../lib/include/classes/SceneHandler.hpp"
#include "../../include/classes/Game.hpp"
#include "../../include/classes/GameScene.hpp"
#include "../../include/classes/SplashScene.hpp"

Game::Game() : IGame(800, 600, "Alien Adventure") {
    auto splashScene = std::make_shared<SplashScene>(this);
    this->getSceneHandler().addActiveScene(splashScene);

    auto gameScene = std::make_shared<GameScene>(this, "Level.txt");
    this->getSceneHandler().addInactiveScene(gameScene);
}

Game::~Game() = default;
