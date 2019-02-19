//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/ObjectHandler.hpp>
#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SceneHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IScene.hpp>

#include <Game/GameOverMenuObject.hpp>
#include <Game/GameScene.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::GameOverMenuObject::GameOverMenuObject(CGL::IGame *game) : CGL::IMenuObject(game, GameScene::DRAW_ORDER_MENU) {
    auto& texture = this->getGame()->getTextureResourceHandler().load("Menu.png");
    this->addItem({0, 64*7, 480, 64}, {0, 64*6, 480, 64}, texture);
    this->addItem({0, 64*5, 480, 64}, {0, 64*4, 480, 64}, texture);
    this->addItem({0, 64*9, 480, 64}, {0, 64*8, 480, 64}, texture);
}

AA::GameOverMenuObject::~GameOverMenuObject() = default;

void AA::GameOverMenuObject::update(const float dt) {
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
