//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "CollectibleHealth.hpp"

#include "CollectibleCoin.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

const std::string SOUND_FILEPATH = "./resources/Health.wav";
const std::string TEXTURE_FILEPATH = "./resources/Hud.png";
const std::string SEQUENCE_ID = "Health";

CollectibleHealth::CollectibleHealth(Game *game, const sf::IntRect spawnArea) : Collectible(game, spawnArea, SOUND_FILEPATH) {
    this->setBoundingBox({ 10, 10, 50, 50 });
}

CollectibleHealth::CollectibleHealth(const CollectibleHealth &original) = default;

CollectibleHealth::~CollectibleHealth() = default;

CollectibleHealth &CollectibleHealth::operator=(const CollectibleHealth &original) {
    return *this;
}

CollectibleHealth *CollectibleHealth::clone() const {
    return new CollectibleHealth(*this);
}

void CollectibleHealth::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        AnimationSequence *sequence = new AnimationSequence(this->getGame(), SEQUENCE_ID, TEXTURE_FILEPATH);
        sequence->addFrame(sf::IntRect(0, 48, 52, 48), 10);
        this->getAnimationHandler()->addSequence(sequence);
        this->getAnimationHandler()->switchSequence(SEQUENCE_ID);
    }
}
