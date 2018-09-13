//
// Created by Emil Hörnlund on 2018-09-13.
//

#include "core/classes/ResourceHandler.hpp"
#include "core/classes/SpriteEntity.hpp"
#include "core/classes/WindowHandler.hpp"
#include "game/classes/Game.hpp"
#include "game/classes/Sun.hpp"

#include <SFML/Graphics/Texture.hpp>

Sun::Sun(IGame *game) : IGameObject(game, Game::DRAW_ORDER_SUN, false) {
    std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Sun.png");
    entity->setTexture(texture);
    entity->setTextureRect({0, 0, 112, 112});
    entity->setOrigin(56.f, 56.f);
    entity->setOffset(this->getGame()->getWindowHandler().getWindowSize().x/2.f, 76.f);
    this->addEntity(entity);
}

Sun::~Sun() = default;

void Sun::restore(const bool respawn) {

}

void Sun::processEvents() {

}

void Sun::update(const float dt) {

}
