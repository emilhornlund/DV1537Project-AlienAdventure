//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SpriteEntity.hpp>

#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/SplashObject.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::SplashObject::SplashObject(CGL::IGame *game) : CGL::IGameObject(game, 0, false) {
    std::shared_ptr<CGL::SpriteEntity> entity = std::make_shared<CGL::SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("Splash.png");
    entity->setTexture(texture);
    entity->setTextureRect({0, 0, 800, 600});
    entity->setOrigin(400, 300);
    entity->setOffset(400, 300);
    this->addEntity(entity);
}

AA::SplashObject::~SplashObject() = default;

void AA::SplashObject::restore(const bool respawn) {

}

void AA::SplashObject::processEvents() {

}

void AA::SplashObject::update(const float dt) {

}
