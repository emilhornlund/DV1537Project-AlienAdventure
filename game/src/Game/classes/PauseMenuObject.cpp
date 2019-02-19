//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "../../../lib/include/classes/ObjectHandler.hpp"
#include "../../../lib/include/classes/ResourceHandler.hpp"
#include "../../../lib/include/classes/SceneHandler.hpp"
#include "../../../lib/include/interfaces/IGame.hpp"
#include "../../../lib/include/interfaces/IScene.hpp"
#include "../../include/classes/PauseMenuObject.hpp"

#include <SFML/Graphics/Texture.hpp>

PauseMenuObject::PauseMenuObject(IGame *game) : IMenuObject(game) {
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
