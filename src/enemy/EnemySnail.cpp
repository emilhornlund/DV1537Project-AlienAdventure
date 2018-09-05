//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "EnemySnail.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

EnemySnail::EnemySnail(Game *game, const sf::IntRect spawnArea) : Enemy(game, spawnArea) {

}

EnemySnail::EnemySnail(const EnemySnail &original) = default;

EnemySnail::~EnemySnail() = default;

EnemySnail &EnemySnail::operator=(const EnemySnail &original) = default;

EnemySnail *EnemySnail::clone() const {
    return new EnemySnail(*this);
}

void EnemySnail::configure() {
    this->setBoundingBox({3, 25, 59, 40});

    this->getAnimationHandler()->clearSequences();

    std::string rpath = "./resources/Enemies.png";

    int posY = 65 * 8;
    AnimationSequence *sequence = new AnimationSequence(this->getGame(), "alive", rpath);
    sequence->addFrame(sf::IntRect(65*0, posY, 65, 65), 0.3);
    sequence->addFrame(sf::IntRect(65*1, posY, 65, 65), 0.3);
    this->getAnimationHandler()->addSequence(sequence);

    AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), "dead", rpath);
    sequenceDead->addFrame(sf::IntRect(65*2, posY, 65, 65), 10);
    this->getAnimationHandler()->addSequence(sequenceDead);
}
