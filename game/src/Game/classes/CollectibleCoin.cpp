//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/classes/AnimatedEntity.hpp>
#include <Core/classes/Animation.hpp>
#include <Core/classes/ResourceHandler.hpp>
#include <Core/interfaces/IGame.hpp>
#include <Game/classes/CollectibleCoin.hpp>

#include <SFML/Graphics/Texture.hpp>

CollectibleCoin::CollectibleCoin(IGame *game, const sf::IntRect &spawnArea) : ICollectible(game, spawnArea, "Coin.wav") {
    this->setBoundingBox({ 10, 10, 50, 50 });

    this->m_animation = std::make_shared<Animation>();
    this->m_animation->addFrame({70 * 8, 70 * 2, 70, 70});
    this->m_animation->setSpriteSheet(this->getGame()->getTextureResourceHandler().load("Misc.png"));
}

CollectibleCoin::~CollectibleCoin() = default;

void CollectibleCoin::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        std::shared_ptr<AnimatedEntity> entity = std::make_shared<AnimatedEntity>();
        entity->setOrigin(35, 35);
        entity->play(*this->m_animation);
        this->addEntity(entity);
    }
}
