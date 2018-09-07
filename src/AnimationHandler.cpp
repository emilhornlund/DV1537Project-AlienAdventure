/**
 * @file AnimationHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "StaticFrame.hpp"

AnimationHandler::AnimationHandler(Game *game) {
    this->game = game;
    this->currentSequence = 0;
}

AnimationHandler::AnimationHandler(const AnimationHandler &original) {
    this->game = original.game;
    this->staticFrames = original.staticFrames;
    this->sequences = original.sequences;
    this->currentSequence = original.currentSequence;
}

AnimationHandler::~AnimationHandler() {
    this->clearStaticFrames();
    this->clearSequences();
}

AnimationHandler& AnimationHandler::operator=(const AnimationHandler &original) {
    if (this != &original) {
        this->game = original.game;
        this->staticFrames = original.staticFrames;
        this->sequences = original.sequences;
        this->currentSequence = original.currentSequence;
    }
    return *this;
}

AnimationHandler* AnimationHandler::clone() const {
    return new AnimationHandler(*this);
}

Game* AnimationHandler::getGame() const {
    return this->game;
}

unsigned long AnimationHandler::numberOfStaticFrames() const {
    return this->staticFrames.size();
}

StaticFrame & AnimationHandler::getStaticFrame(const unsigned int index) const {
    return *this->staticFrames[index];
}

void AnimationHandler::addStaticFrame(StaticFrame *frame) {
    std::shared_ptr<StaticFrame> sharedPtr;
    sharedPtr.reset(frame);
    this->staticFrames.push_back(sharedPtr);
}

void AnimationHandler::clearStaticFrames() {
    this->staticFrames.clear();
}

void AnimationHandler::addSequence(AnimationSequence *sequence) {
    std::shared_ptr<AnimationSequence> sharedPtr;
    sharedPtr.reset(sequence);
    this->sequences.push_back(sharedPtr);
}

bool AnimationHandler::switchSequence(const std::string &identifier) {
    bool found = false;
    for (unsigned int i = 0; i < this->sequences.size() && !found; i++) {
        if (this->sequences[i]->getIdentifier() == identifier) {
            found = true;
            this->currentSequence = i;
        }
    }
    return found;
}

AnimationSequence & AnimationHandler::getCurrentSequence() {
    return *this->sequences[this->currentSequence];
}

int AnimationHandler::numberOfSequences() const {
    return this->sequences.size();
}

void AnimationHandler::clearSequences() {
    this->sequences.clear();
    this->currentSequence = 0;
}
