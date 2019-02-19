//
// Created by Emil Hörnlund on 2018-09-13.
//

#include <Core/ResourceHandler.hpp>
#include <Core/SpriteEntity.hpp>
#include <Core/WindowHandler.hpp>

#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/Sun.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::Sun::Sun(CGL::IGame *game) : IGameObject(game, GameScene::DRAW_ORDER_SUN, false) {
    std::shared_ptr<CGL::SpriteEntity> entity = std::make_shared<CGL::SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("Sun.png");
    entity->setTexture(texture);
    entity->setTextureRect({0, 0, 112, 112});
    entity->setOrigin(56.f, 56.f);
    entity->setOffset(this->getGame()->getWindowHandler().getWindowSize().x/2.f, 76.f);
    this->addEntity(entity);
}

AA::Sun::~Sun() = default;

void AA::Sun::restore(const bool respawn) {

}

void AA::Sun::processEvents() {

}

void AA::Sun::update(const float dt) {

}
