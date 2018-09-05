//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "EnemyBeeBlack.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

EnemyBeeBlack::EnemyBeeBlack(Game *game, const sf::IntRect spawnArea) : Enemy(game, spawnArea) {

}

EnemyBeeBlack::EnemyBeeBlack(const EnemyBeeBlack &original) = default;

EnemyBeeBlack::~EnemyBeeBlack() = default;

EnemyBeeBlack &EnemyBeeBlack::operator=(const EnemyBeeBlack &original) = default;

EnemyBeeBlack *EnemyBeeBlack::clone() const {
    return new EnemyBeeBlack(*this);
}

void EnemyBeeBlack::configure() {
    this->setBoundingBox({5, 21, 55, 48});

    this->getAnimationHandler()->clearSequences();

    std::string rpath = "./resources/Enemies.png";

    int posY = 65 * 7;
    AnimationSequence *sequence = new AnimationSequence(this->getGame(), "alive", rpath);
    sequence->addFrame(sf::IntRect(65*0, posY, 65, 65), 0.3);
    sequence->addFrame(sf::IntRect(65*1, posY, 65, 65), 0.3);
    this->getAnimationHandler()->addSequence(sequence);

    AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), "dead", rpath);
    sequenceDead->addFrame(sf::IntRect(65*2, posY, 65, 65), 10);
    this->getAnimationHandler()->addSequence(sequenceDead);
}
