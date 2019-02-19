//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <Core/AnimatedEntity.hpp>
#include <Core/Animation.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/IGame.hpp>

#include <Game/CollectibleCoin.hpp>

#include <SFML/Graphics/Texture.hpp>

AA::CollectibleCoin::CollectibleCoin(CGL::IGame *game, const sf::IntRect &spawnArea) : ICollectible(game, spawnArea, "Coin.wav") {
    this->setBoundingBox({ 10, 10, 50, 50 });

    this->m_animation = std::make_shared<CGL::Animation>();
    this->m_animation->addFrame({70 * 8, 70 * 2, 70, 70});
    this->m_animation->setSpriteSheet(this->getGame()->getTextureResourceHandler().load("Misc.png"));
}

AA::CollectibleCoin::~CollectibleCoin() = default;

void AA::CollectibleCoin::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        std::shared_ptr<CGL::AnimatedEntity> entity = std::make_shared<CGL::AnimatedEntity>();
        entity->setOrigin(35, 35);
        entity->play(*this->m_animation);
        this->addEntity(entity);
    }
}
