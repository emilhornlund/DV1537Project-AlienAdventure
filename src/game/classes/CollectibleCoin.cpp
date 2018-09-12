//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "core/classes/AnimatedEntity.hpp"
#include "core/classes/Animation.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/CollectibleCoin.hpp"

#include <SFML/Graphics/Texture.hpp>

CollectibleCoin::CollectibleCoin(IGame *game, const sf::IntRect &spawnArea) : ICollectible(game, spawnArea, "./resources/Coin.wav") {
    this->setBoundingBox({ 10, 10, 50, 50 });

    this->m_animation = std::make_shared<Animation>();
    this->m_animation->addFrame({70 * 8, 70 * 2, 70, 70});
    this->m_animation->setSpriteSheet(this->getGame()->getTextureResourceHandler().load("./resources/Misc.png"));
}

CollectibleCoin::~CollectibleCoin() = default;

void CollectibleCoin::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        auto* entity = new AnimatedEntity();
        entity->setOrigin(35, 35);
        entity->play(*this->m_animation);
        this->addEntity(entity);
    }
}
