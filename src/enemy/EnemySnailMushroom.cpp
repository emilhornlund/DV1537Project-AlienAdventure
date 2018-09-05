//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "EnemySnailMushroom.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

EnemySnailMushroom::EnemySnailMushroom(Game *game, const sf::IntRect spawnArea) : Enemy(game, spawnArea) {

}

EnemySnailMushroom::EnemySnailMushroom(const EnemySnailMushroom &original) = default;

EnemySnailMushroom::~EnemySnailMushroom() = default;

EnemySnailMushroom &EnemySnailMushroom::operator=(const EnemySnailMushroom &original) = default;

EnemySnailMushroom *EnemySnailMushroom::clone() const {
    return new EnemySnailMushroom(*this);
}

void EnemySnailMushroom::configure() {
    this->setBoundingBox({3, 25, 59, 40});

    this->getAnimationHandler()->clearSequences();

    std::string rpath = "./resources/Enemies.png";

    int posY = 65 * 9;
    AnimationSequence *sequence = new AnimationSequence(this->getGame(), "alive", rpath);
    sequence->addFrame(sf::IntRect(65*0, posY, 65, 65), 0.3);
    sequence->addFrame(sf::IntRect(65*1, posY, 65, 65), 0.3);
    this->getAnimationHandler()->addSequence(sequence);

    AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), "dead", rpath);
    sequenceDead->addFrame(sf::IntRect(65*2, posY, 65, 65), 10);
    this->getAnimationHandler()->addSequence(sequenceDead);
}
