//
// Created by Emil Hörnlund on 2018-09-07.
//

#include "AnimationHandler.hpp"
#include "CollectibleBarObject.hpp"
#include "Game.hpp"
#include "PropertyHandler.hpp"

#include <iostream>
#include <CollectibleBarObject.hpp>


const float SPRITE_WIDTH = 52;
const float SPRITE_HEIGHT = 48;

const float SPACE = 10;

CollectibleBarObject::CollectibleBarObject(Game *game) : GameObject(game, false) {
    this->currentCoins = 0;

    this->createCoin();
    this->createMultiplier();
    this->createFirstDigitCoin();
}

CollectibleBarObject::CollectibleBarObject(const CollectibleBarObject &original) : GameObject(original) {
    this->currentCoins = original.currentCoins;
}

CollectibleBarObject &CollectibleBarObject::operator=(const CollectibleBarObject &original) {
    if (this != &original) {
        this->currentCoins = original.currentCoins;
    }
    return *this;
}

CollectibleBarObject::~CollectibleBarObject() = default;

GameObject *CollectibleBarObject::clone() const {
    return new CollectibleBarObject(*this);
}

void CollectibleBarObject::restore(const bool respawn) {
    if (!respawn) {
        this->currentCoins = 0;
        this->getAnimationHandler()->clearStaticFrames();

        this->createCoin();
        this->createMultiplier();
        this->createFirstDigitCoin();
    }
}

void CollectibleBarObject::processEvents() {

}

void CollectibleBarObject::update(const float dt) {
    if (!this->getGame()->getPropertyHandler()->hasProperty("coins")) {
        this->getAnimationHandler()->clearStaticFrames();
        return;
    }
    auto value = this->getGame()->getPropertyHandler()->get<unsigned int>("coins");
    if (this->currentCoins != value) {
        this->currentCoins = value;
        auto ndigits = (int)std::to_string(value).size();
        auto nframes = (unsigned int)this->getAnimationHandler()->numberOfStaticFrames();
        if (ndigits > nframes - 2) {
            //TODO: make more than 9 coins of 1 digit possible
        } else {
            for (unsigned int i = 0; i < (nframes - 2); i++) {
                int digit = std::to_string(value)[i] - '0';
                auto *frame = dynamic_cast<SpriteStaticFrame*>(&this->getAnimationHandler()->getStaticFrame(i+2));
                if (frame != nullptr) {
                    auto &sprite = frame->getSprite();
                    sprite.setTextureRect({(int)SPRITE_WIDTH*(digit+1), (int)SPRITE_HEIGHT*3, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
                }
            }
        }
    }
}

void CollectibleBarObject::createCoin() {
    auto *frame = new SpriteStaticFrame(this->getGame());
    frame->loadSpriteTextureFromFile("./resources/Hud.png");
    this->getAnimationHandler()->addStaticFrame(frame);

    auto &sprite = frame->getSprite();
    sprite.setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
    sprite.setPosition(800 - SPACE - sprite.getOrigin().x, SPACE + sprite.getOrigin().y);
    sprite.setTextureRect({(int)SPRITE_WIDTH*3, (int)SPRITE_HEIGHT, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
}

void CollectibleBarObject::createMultiplier() {
    auto *frame = new SpriteStaticFrame(this->getGame());
    frame->loadSpriteTextureFromFile("./resources/Hud.png");
    this->getAnimationHandler()->addStaticFrame(frame);

    auto &sprite = frame->getSprite();
    sprite.setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
    auto maxX = 800 - SPACE - SPRITE_WIDTH - sprite.getOrigin().x;
    sprite.setPosition(maxX - sprite.getOrigin().x - SPACE, SPACE + sprite.getOrigin().y + 4);
    sprite.setTextureRect({0, (int)SPRITE_HEIGHT*3, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
}

void CollectibleBarObject::createFirstDigitCoin() {
    auto *frame = new SpriteStaticFrame(this->getGame());
    frame->loadSpriteTextureFromFile("./resources/Hud.png");
    this->getAnimationHandler()->addStaticFrame(frame);

    auto &sprite = frame->getSprite();
    sprite.setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
    auto maxX = 800 - SPACE - SPRITE_WIDTH - sprite.getOrigin().x;
    sprite.setPosition(maxX, sprite.getOrigin().y + SPACE);
    sprite.setTextureRect({(int)SPRITE_WIDTH, (int)SPRITE_HEIGHT*3, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
}

CollectibleBarObject::SpriteStaticFrame::SpriteStaticFrame(Game *game) : StaticFrame(game) {
    this->sprite = new sf::Sprite();
}

CollectibleBarObject::SpriteStaticFrame::SpriteStaticFrame(const CollectibleBarObject::SpriteStaticFrame &original) : StaticFrame(original) {
    this->sprite = new sf::Sprite(*original.sprite);
}

CollectibleBarObject::SpriteStaticFrame::~SpriteStaticFrame() {
    delete this->sprite;
    this->sprite = nullptr;
}

CollectibleBarObject::SpriteStaticFrame &CollectibleBarObject::SpriteStaticFrame::operator=(const CollectibleBarObject::SpriteStaticFrame &original) {
    if (this != &original) {
        this->sprite = new sf::Sprite(*original.sprite);
    }
    return *this;
}

CollectibleBarObject::SpriteStaticFrame *CollectibleBarObject::SpriteStaticFrame::clone() const {
    return new SpriteStaticFrame(*this);
}

void CollectibleBarObject::SpriteStaticFrame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(*this->sprite);
}

sf::Sprite &CollectibleBarObject::SpriteStaticFrame::getSprite() const {
    return *this->sprite;
}

void CollectibleBarObject::SpriteStaticFrame::loadSpriteTextureFromFile(const std::string filePath) {
    if (this->loadTextureFromFile(filePath)) {
        this->sprite->setTexture(*this->getTexture());
    }
}
