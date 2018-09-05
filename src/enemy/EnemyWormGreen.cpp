//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "EnemyWormGreen.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

EnemyWormGreen::EnemyWormGreen(Game *game, const sf::IntRect spawnArea) : Enemy(game, spawnArea) {

}

EnemyWormGreen::EnemyWormGreen(const EnemyWormGreen &original) = default;

EnemyWormGreen::~EnemyWormGreen() = default;

EnemyWormGreen &EnemyWormGreen::operator=(const EnemyWormGreen &original) = default;

EnemyWormGreen *EnemyWormGreen::clone() const {
    return new EnemyWormGreen(*this);
}

void EnemyWormGreen::configure() {
    this->setBoundingBox({4, 43, 57, 22});

    this->getAnimationHandler()->clearSequences();

    std::string rpath = "./resources/Enemies.png";

    int posY = 65 * 13;
    AnimationSequence *sequence = new AnimationSequence(this->getGame(), "alive", rpath);
    sequence->addFrame(sf::IntRect(65*0, posY, 65, 65), 0.3);
    sequence->addFrame(sf::IntRect(65*1, posY, 65, 65), 0.3);
    this->getAnimationHandler()->addSequence(sequence);

    AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), "dead", rpath);
    sequenceDead->addFrame(sf::IntRect(65*2, posY, 65, 65), 10);
    this->getAnimationHandler()->addSequence(sequenceDead);
}
