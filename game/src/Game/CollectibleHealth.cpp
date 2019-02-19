//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/AnimatedEntity.hpp>
#include <Core/Animation.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/IGame.hpp>

#include <Game/CollectibleHealth.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::CollectibleHealth::CollectibleHealth(CGL::IGame *game, const sf::IntRect &spawnArea) : ICollectible(game, spawnArea, "Health.wav") {
    this->setBoundingBox({ 10, 10, 50, 50 });

    this->m_animation = std::make_shared<CGL::Animation>();
    this->m_animation->addFrame({0, 48, 52, 48});
    this->m_animation->setSpriteSheet( this->getGame()->getTextureResourceHandler().load("Hud.png"));
}

AA::CollectibleHealth::~CollectibleHealth() = default;

void AA::CollectibleHealth::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        std::shared_ptr<CGL::AnimatedEntity> entity = std::make_shared<CGL::AnimatedEntity>();
        entity->setOrigin(26, 24);
        entity->play(*this->m_animation);
        this->addEntity(entity);
    }
}
