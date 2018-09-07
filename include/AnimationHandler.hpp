/**
 * @file AnimationHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef ANIMATION_HANDLER_HPP
#define ANIMATION_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

#include <memory>

class AnimationHandler {
private:
    Game* game;

    std::vector<std::shared_ptr<StaticFrame>> staticFrames;

    std::vector<std::shared_ptr<AnimationSequence>> sequences;

    unsigned int currentSequence;
public:
    explicit AnimationHandler(Game *game);

    AnimationHandler(const AnimationHandler &original);

    virtual ~AnimationHandler();

    AnimationHandler& operator=(const AnimationHandler &original);

    virtual AnimationHandler* clone() const;

    Game* getGame() const;

    unsigned long numberOfStaticFrames() const;

    StaticFrame& getStaticFrame(const unsigned int index) const;

    void addStaticFrame(StaticFrame *frame);

    void clearStaticFrames();

    void addSequence(AnimationSequence *sequence);

    bool switchSequence(const std::string &identifier);

    AnimationSequence& getCurrentSequence();

    int numberOfSequences() const;

    void clearSequences();
};

#endif /* AnimationHandler_hpp */
