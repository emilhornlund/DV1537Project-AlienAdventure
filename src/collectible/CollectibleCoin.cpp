//
// Created by Emil Hörnlund on 2018-09-05.
//

#include <collectible/CollectibleCoin.hpp>

#include "collectible/CollectibleCoin.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

const std::string SOUND_FILEPATH = "./resources/Coin.wav";
const std::string TEXTURE_FILEPATH = "./resources/Misc.png";
const std::string SEQUENCE_ID = "Coin";

CollectibleCoin::CollectibleCoin(Game *game, const sf::IntRect spawnArea) : Collectible(game, spawnArea, SOUND_FILEPATH) {
    this->setBoundingBox({ 10, 10, 50, 50 });
}

CollectibleCoin::CollectibleCoin(const CollectibleCoin &original) = default;

CollectibleCoin::~CollectibleCoin() = default;

CollectibleCoin &CollectibleCoin::operator=(const CollectibleCoin &original) {
    return *this;
}

CollectibleCoin *CollectibleCoin::clone() const {
    return new CollectibleCoin(*this);
}

void CollectibleCoin::restore(const bool respawn) {
    if (!respawn) {
        this->setCollected(false);

        AnimationSequence *sequence = new AnimationSequence(this->getGame(), SEQUENCE_ID, TEXTURE_FILEPATH);
        sequence->addFrame(sf::IntRect(70 * 8, 70 * 2, 70, 70), 10);
        this->getAnimationHandler()->addSequence(sequence);
        this->getAnimationHandler()->switchSequence(SEQUENCE_ID);
    }
}
