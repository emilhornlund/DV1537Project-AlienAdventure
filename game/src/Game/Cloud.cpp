//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SpriteEntity.hpp>

#include <Game/Cloud.hpp>
#include <Game/Game.hpp>
#include <Game/GameScene.hpp>

#include <SFML/Graphics/Texture.hpp>

#include <random>
#include <functional>

const unsigned int SPEED_MIN = 20;
const unsigned int SPEED_MAX = 50;

AA::Cloud::Cloud(CGL::IGame *game, const sf::IntRect &spawnArea) : IGameObject(game, GameScene::DRAW_ORDER_BACKGROUND, true), m_spawnArea(spawnArea) {
    auto newZIndex = this->randomZIndex();
    this->setZIndex(newZIndex);

    std::shared_ptr<CGL::SpriteEntity> entity = std::make_shared<CGL::SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("Cloud1.png");
    entity->setTexture(texture);
    entity->setTextureRect({ 0, 0, (int)texture.getSize().x, (int)texture.getSize().y });
    entity->setOrigin(texture.getSize().x/2.f, texture.getSize().y/2.f);

    auto offsetX = std::bind(std::uniform_int_distribution<>(spawnArea.left,spawnArea.left+spawnArea.width),std::default_random_engine(std::random_device{}()))();
    auto offsetY = std::bind(std::uniform_int_distribution<>(spawnArea.top,spawnArea.top+spawnArea.height),std::default_random_engine(std::random_device{}()))();
    entity->setOffset(offsetX, offsetY);

    this->addEntity(entity);
    this->m_entity = entity;

    this->m_speed = this->randomSpeed();
}

AA::Cloud::~Cloud() = default;

void AA::Cloud::restore(const bool respawn) {

}

void AA::Cloud::processEvents() {

}

void AA::Cloud::update(const float dt) {
    auto offset = this->m_entity->getOffset();
    offset.x += dt * this->m_speed;
    this->m_entity->setOffset(offset);

    const auto worldSize = this->getGame()->getPropertyHandler().get<sf::Vector2i>("worldSize");

    if (offset.x - this->m_entity->getOrigin().x > worldSize.x) {
        offset.x = -(this->m_entity->getOrigin().x);
        offset.y = std::bind(std::uniform_int_distribution<>(this->m_spawnArea.top,this->m_spawnArea.top+this->m_spawnArea.height),std::default_random_engine(std::random_device{}()))();
        this->m_entity->setOffset(offset);

        auto newZIndex = this->randomZIndex();
        this->setZIndex(newZIndex);

        this->m_speed = this->randomSpeed();
    }
}

int AA::Cloud::randomZIndex() const {
    auto zIndex = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine(std::random_device{}()))();
    if (zIndex == 0) {
        return GameScene::DRAW_ORDER_CLOUD_LAYER1;
    } else {
        return GameScene::DRAW_ORDER_CLOUD_LAYER2;
    }
}

float AA::Cloud::randomSpeed() const {
    auto speed = (float)std::bind(std::uniform_real_distribution<>(SPEED_MIN,SPEED_MAX),std::default_random_engine(std::random_device{}()))();
    return speed;
}
