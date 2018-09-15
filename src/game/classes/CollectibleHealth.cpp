//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "core/classes/AnimatedEntity.hpp"
#include "core/classes/Animation.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/CollectibleHealth.hpp"

#include <SFML/Graphics/Texture.hpp>

CollectibleHealth::CollectibleHealth(IGame *game, const sf::IntRect &spawnArea) : ICollectible(game, spawnArea, "Health.wav") {
    this->setBoundingBox({ 10, 10, 50, 50 });

    this->m_animation = std::make_shared<Animation>();
    this->m_animation->addFrame({0, 48, 52, 48});
    this->m_animation->setSpriteSheet( this->getGame()->getTextureResourceHandler().load("Hud.png"));
}

CollectibleHealth::~CollectibleHealth() = default;

void CollectibleHealth::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        std::shared_ptr<AnimatedEntity> entity = std::make_shared<AnimatedEntity>();
        entity->setOrigin(26, 24);
        entity->play(*this->m_animation);
        this->addEntity(entity);
    }
}
