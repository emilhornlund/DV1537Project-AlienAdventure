//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/ObjectHandler.hpp>
#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SceneHandler.hpp>
#include <Core/IGame.hpp>
#include <Core/IScene.hpp>

#include <Game/LevelCompleteMenuObject.hpp>
#include <Game/GameScene.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::LevelCompleteMenuObject::LevelCompleteMenuObject(CGL::IGame *game) : IMenuObject(game, GameScene::DRAW_ORDER_MENU) {
    auto& texture = this->getGame()->getTextureResourceHandler().load("Menu.png");
    this->addItem({0, 64*1, 480, 64}, {0, 64*0, 480, 64}, texture);
    this->addItem({0, 64*9, 480, 64}, {0, 64*8, 480, 64}, texture);
}

AA::LevelCompleteMenuObject::~LevelCompleteMenuObject() = default;

void AA::LevelCompleteMenuObject::update(const float dt) {
    const auto index = this->getSelectedItemIndex();
    if (index >= 0) {
        auto& scene = this->getGame()->getSceneHandler().getActiveScene();
        switch (index) {
            case 0:
                scene.getObjectHandler().restoreObjects(true);
                break;
            case 1:
                this->getGame()->quit(0);
                break;
            default:
                break;
        }
        this->getGame()->getPropertyHandler().set<bool>("levelComplete", false);
        this->restore(false);
        this->getGame()->closeMenu();
    }
}
