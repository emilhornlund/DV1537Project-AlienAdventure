//
// Created by Emil Hörnlund on 2018-09-05.
//

#include "EnemySlimeGreen.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"

EnemySlimeGreen::EnemySlimeGreen(Game *game, const sf::IntRect spawnArea) : Enemy(game, spawnArea) {

}

EnemySlimeGreen::~EnemySlimeGreen() = default;

void EnemySlimeGreen::configure() {
    this->setBoundingBox({8, 31, 49, 34});

    this->getAnimationHandler()->clearSequences();

    std::string rpath = "./resources/Enemies.png";

    int posY = 65 * 1;
    AnimationSequence *sequence = new AnimationSequence(this->getGame(), "alive", rpath);
    sequence->addFrame(sf::IntRect(65*0, posY, 65, 65), 0.3);
    sequence->addFrame(sf::IntRect(65*1, posY, 65, 65), 0.3);
    sequence->addFrame(sf::IntRect(65*2, posY, 65, 65), 0.3);
    this->getAnimationHandler()->addSequence(sequence);

    AnimationSequence *sequenceDead = new AnimationSequence(this->getGame(), "dead", rpath);
    sequenceDead->addFrame(sf::IntRect(65*3, posY, 65, 65), 10);
    this->getAnimationHandler()->addSequence(sequenceDead);
}
