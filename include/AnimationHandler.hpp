/**
 * @file AnimationHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef ANIMATION_HANDLER_HPP
#define ANIMATION_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class AnimationHandler {
private:
    unsigned int staticFramesCapacity;

    unsigned int staticFramesSize;

    StaticFrame** staticFrames;

    unsigned int sequencesCapacity;

    unsigned int sequencesSize;

    unsigned int currentSequence;

    AnimationSequence** sequences;
public:
    AnimationHandler();

    AnimationHandler(const AnimationHandler &original);

    virtual ~AnimationHandler();

    virtual AnimationHandler& operator=(const AnimationHandler &original);

    virtual AnimationHandler* clone() const;

    int numberOfStaticFrames() const;

    StaticFrame* getStaticFrame(const unsigned int index) const;

    void addStaticFrame(StaticFrame *frame);

    void clearStaticFrames();

    void addSequence(AnimationSequence *sequence);

    bool switchSequence(const std::string &identifier);

    AnimationSequence* getCurrentSequence();

    int numberOfSequences() const;

    void clearSequences();
};

#endif /* AnimationHandler_hpp */
