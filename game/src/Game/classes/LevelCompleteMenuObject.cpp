//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/classes/ObjectHandler.hpp>
#include <Core/classes/PropertyHandler.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/classes/SceneHandler.hpp>
#include <Core/interfaces/IGame.hpp>
#include <Core/interfaces/IScene.hpp>
#include <Game/classes/LevelCompleteMenuObject.hpp>

#include <SFML/Graphics/Texture.hpp>

LevelCompleteMenuObject::LevelCompleteMenuObject(IGame *game) : IMenuObject(game) {
    auto& texture = this->getGame()->getTextureResourceHandler().load("Menu.png");
    this->addItem({0, 64*1, 480, 64}, {0, 64*0, 480, 64}, texture);
    this->addItem({0, 64*9, 480, 64}, {0, 64*8, 480, 64}, texture);
}

LevelCompleteMenuObject::~LevelCompleteMenuObject() = default;

void LevelCompleteMenuObject::update(const float dt) {
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
