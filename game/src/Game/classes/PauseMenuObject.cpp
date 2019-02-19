//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/classes/ObjectHandler.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/classes/SceneHandler.hpp>
#include <Core/interfaces/IGame.hpp>
#include <Core/interfaces/IScene.hpp>

#include <Game/classes/PauseMenuObject.hpp>
#include <Game/classes/GameScene.hpp>

#include <SFML/Graphics/Texture.hpp>

PauseMenuObject::PauseMenuObject(IGame *game) : IMenuObject(game, GameScene::DRAW_ORDER_MENU) {
    auto& texture = this->getGame()->getTextureResourceHandler().load("Menu.png");
    this->addItem({0, 64*3, 480, 64}, {0, 64*2, 480, 64}, texture);
    this->addItem({0, 64*5, 480, 64}, {0, 64*4, 480, 64}, texture);
    this->addItem({0, 64*9, 480, 64}, {0, 64*8, 480, 64}, texture);
}

PauseMenuObject::~PauseMenuObject() = default;

void PauseMenuObject::update(const float dt) {
    const auto index = this->getSelectedItemIndex();
    if (index >= 0) {
        auto& scene = this->getGame()->getSceneHandler().getActiveScene();
        switch (index) {
            case 0:
                scene.resume();
                break;
            case 1:
                scene.resume();
                scene.getObjectHandler().restoreObjects(false);
                break;
            case 2:
                this->getGame()->quit(0);
                break;
            default:
                break;
        }
        this->restore(false);
        this->getGame()->closeMenu();
    }
}
