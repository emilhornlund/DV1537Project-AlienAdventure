//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/ObjectHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SceneHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IScene.hpp>

#include <Game/PauseMenuObject.hpp>
#include <Game/GameScene.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::PauseMenuObject::PauseMenuObject(CGL::IGame *game) : IMenuObject(game, GameScene::DRAW_ORDER_MENU) {
    auto& texture = this->getGame()->getTextureResourceHandler().load("Menu.png");
    this->addItem({0, 64*3, 480, 64}, {0, 64*2, 480, 64}, texture);
    this->addItem({0, 64*5, 480, 64}, {0, 64*4, 480, 64}, texture);
    this->addItem({0, 64*9, 480, 64}, {0, 64*8, 480, 64}, texture);
}

AA::PauseMenuObject::~PauseMenuObject() = default;

void AA::PauseMenuObject::update(const float dt) {
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
