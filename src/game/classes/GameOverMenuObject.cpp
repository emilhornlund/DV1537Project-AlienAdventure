//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "core/classes/ObjectHandler.hpp"
#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/SceneHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "core/interfaces/IScene.hpp"
#include "game/classes/GameOverMenuObject.hpp"

#include <SFML/Graphics/Texture.hpp>

GameOverMenuObject::GameOverMenuObject(IGame *game) : IMenuObject(game) {
    auto& texture = this->getGame()->getTextureResourceHandler().load("./resources/Menu.png");
    this->addItem({0, 64*7, 480, 64}, {0, 64*6, 480, 64}, texture);
    this->addItem({0, 64*5, 480, 64}, {0, 64*4, 480, 64}, texture);
    this->addItem({0, 64*9, 480, 64}, {0, 64*8, 480, 64}, texture);
}

GameOverMenuObject::~GameOverMenuObject() = default;

void GameOverMenuObject::update(const float dt) {
    const auto index = this->getSelectedItemIndex();
    if (index >= 0) {
        auto& scene = this->getGame()->getSceneHandler().getActiveScene();
        switch (index) {
            case 0:
                scene.getObjectHandler().restoreObjects(true);
                break;
            case 1:
                scene.getObjectHandler().restoreObjects(false);
                break;
            case 2:
                this->getGame()->quit(0);
                break;
            default:
                break;
        }
        this->getGame()->getPropertyHandler().set<bool>("gameOver", false);
        this->restore(false);
        this->getGame()->closeMenu();
    }
}