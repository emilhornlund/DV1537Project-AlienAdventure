//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/SpriteEntity.hpp"
#include "game/classes/Game.hpp"
#include "game/classes/GameScene.hpp"
#include "game/classes/SplashObject.hpp"

#include <SFML/Graphics/Texture.hpp>

SplashObject::SplashObject(IGame *game) : IGameObject(game, 0, false) {
    std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Splash.png");
    entity->setTexture(texture);
    entity->setTextureRect({0, 0, 800, 600});
    entity->setOrigin(400, 300);
    entity->setOffset(400, 300);
    this->addEntity(entity);
}

SplashObject::~SplashObject() = default;

void SplashObject::restore(const bool respawn) {

}

void SplashObject::processEvents() {

}

void SplashObject::update(const float dt) {

}
