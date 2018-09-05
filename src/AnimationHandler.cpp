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

    this->staticFramesCapacity = 0;
    this->staticFramesSize = 0;
    this->staticFrames = new StaticFrame *[this->staticFramesCapacity];

    this->sequencesCapacity = 0;
    this->sequencesSize = 0;
    this->currentSequence = 0;
    this->sequences = new AnimationSequence*[this->sequencesCapacity];
}

AnimationHandler::AnimationHandler(const AnimationHandler &original) {
    this->game = original.getGame();

    this->staticFramesCapacity = original.staticFramesCapacity;
    this->staticFramesSize = original.staticFramesSize;
    this->staticFrames = new StaticFrame *[this->staticFramesCapacity];
    for (int i = 0; i < this->staticFramesSize; i++) {
        this->staticFrames[i] = original.staticFrames[i]->clone();
    }

    this->sequencesSize = original.sequencesSize;
    this->sequencesCapacity = original.sequencesCapacity;
    this->sequences = new AnimationSequence*[this->sequencesCapacity];
    for (int i = 0; i < this->sequencesSize; i++) {
        this->sequences[i] = original.sequences[i]->clone();
    }
    this->currentSequence = original.currentSequence;
}

AnimationHandler::~AnimationHandler() {
    this->clearStaticFrames();
    this->clearSequences();
}

AnimationHandler& AnimationHandler::operator=(const AnimationHandler &original) {
    if (this != &original) {
        this->game = original.getGame();

        for (int i = 0; i < this->staticFramesSize; i++) {
            delete this->staticFrames[i];
            this->staticFrames[i] = nullptr;
        }
        delete[] this->staticFrames;
        this->staticFrames = nullptr;

        this->staticFramesCapacity = original.staticFramesCapacity;
        this->staticFramesSize = original.staticFramesSize;
        this->staticFrames = new StaticFrame *[this->staticFramesCapacity];

        for (int i = 0; i < this->staticFramesSize; i++) {
            this->staticFrames[i] = original.staticFrames[i]->clone();
        }

        for (int i = 0; i < this->sequencesSize; i++) {
            delete this->sequences[i];
            this->sequences[i] = nullptr;
        }
        delete[] this->sequences;
        this->sequences = nullptr;

        this->sequencesSize = original.sequencesSize;
        this->sequencesCapacity = original.sequencesCapacity;
        this->sequences = new AnimationSequence*[this->sequencesCapacity];

        for (int i = 0; i < this->sequencesSize; i++) {
            this->sequences[i] = original.sequences[i]->clone();
        }
    }
    return *this;
}

AnimationHandler* AnimationHandler::clone() const {
    return new AnimationHandler(*this);
}

Game* AnimationHandler::getGame() const {
    return this->game;
}

int AnimationHandler::numberOfStaticFrames() const {
    return this->staticFramesSize;
}

StaticFrame* AnimationHandler::getStaticFrame(const unsigned int index) const {
    return this->staticFrames[index];
}

void AnimationHandler::addStaticFrame(StaticFrame *frame) {
    if (this->staticFramesCapacity == this->staticFramesSize) {
        this->staticFramesCapacity += 5;
        auto **tempStaticFrames = new StaticFrame *[this->staticFramesCapacity];
        for (int i = 0; i < this->staticFramesSize; i++) {
            tempStaticFrames[i] = this->staticFrames[i]->clone();
        }
        this->clearStaticFrames();
        this->staticFrames = tempStaticFrames;
    }
    this->staticFrames[this->staticFramesSize] = frame;
    this->staticFramesSize++;
}

void AnimationHandler::clearStaticFrames() {
    for (int i = 0; i < this->staticFramesSize; i++) {
        delete this->staticFrames[i];
        this->staticFrames[i] = nullptr;
    }
    delete[] this->staticFrames;
    this->staticFrames = nullptr;
}

void AnimationHandler::addSequence(AnimationSequence *sequence) {
    if (this->sequencesCapacity == this->sequencesSize) {
        this->sequencesCapacity += 5;
        auto **tempSequences = new AnimationSequence*[this->sequencesCapacity];
        for (int i = 0; i < this->sequencesSize; i++) {
            tempSequences[i] = this->sequences[i]->clone();
        }
        for (int i = 0; i < this->sequencesSize; i++) {
            delete this->sequences[i];
            this->sequences[i] = nullptr;
        }
        delete[] this->sequences;
        this->sequences = nullptr;
        this->sequences = tempSequences;
    }

    this->sequences[this->sequencesSize] = sequence;
    this->sequencesSize++;
}

bool AnimationHandler::switchSequence(const std::string &identifier) {
    bool found = false;
    for (unsigned int i = 0; i < this->sequencesSize && !found; i++) {
        if (this->sequences[i]->getIdentifier() == identifier) {
            found = true;
            this->currentSequence = i;
        }
    }
    return found;
}

AnimationSequence* AnimationHandler::getCurrentSequence() {
    AnimationSequence* sequence = nullptr;
    if (this->sequencesSize > 0 && this->currentSequence < this->sequencesSize) {
        sequence = this->sequences[this->currentSequence];
    }
    return sequence;
}

int AnimationHandler::numberOfSequences() const {
    return this->sequencesSize;
}

void AnimationHandler::clearSequences() {
    for (int i = 0; i < this->sequencesSize; i++) {
        delete this->sequences[i];
        this->sequences[i] = nullptr;
    }
    delete[] this->sequences;
    this->sequences = nullptr;

    this->sequencesCapacity = 0;
    this->sequencesSize = 0;
}
