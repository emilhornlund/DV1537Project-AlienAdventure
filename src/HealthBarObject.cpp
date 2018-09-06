//
// Created by Emil Hörnlund on 2018-09-06.
//

#include "AnimationHandler.hpp"
#include "Game.hpp"
#include "HealthBarObject.hpp"
#include "PropertyHandler.hpp"

const float SPRITE_WIDTH = 52;
const float SPRITE_HEIGHT = 48;

const float SPACE = 10;

HealthBarObject::HealthBarObject(Game *game) : GameObject(game, false) {
    this->currentHealth = 0;
}

HealthBarObject::HealthBarObject(const HealthBarObject &original) : GameObject(original) {
    this->currentHealth = original.currentHealth;
}

HealthBarObject &HealthBarObject::operator=(const HealthBarObject &original) {
    if (this != &original) {
        this->currentHealth = original.currentHealth;
    }
    return *this;
}

HealthBarObject::~HealthBarObject() = default;

GameObject *HealthBarObject::clone() const {
    return new HealthBarObject(*this);
}

void HealthBarObject::restore(const bool respawn) {
    if (!respawn) {
//        this->currentHealth = 0;
//        this->getAnimationHandler()->clearStaticFrames();
    }
}

void HealthBarObject::processEvents() {

}

void HealthBarObject::update(const float dt) {
    if (!this->getGame()->getPropertyHandler()->hasProperty("health")) {
        this->getAnimationHandler()->clearStaticFrames();
        return;
    }
    auto value = this->getGame()->getPropertyHandler()->get<unsigned int>("health");
    if (this->currentHealth != value) {
        this->currentHealth = value;
        ///add extra health frames if needed
        auto nframes = this->getAnimationHandler()->numberOfStaticFrames();
        if (value > nframes) {
            auto n = value - nframes;
            for (int i = 0; i < n; i++) {
                auto *frame = new HealthBarObjectStaticFrame(this->getGame());
                this->getAnimationHandler()->addStaticFrame(frame);
            }
        }
        ///position and update the texture rect for every frame and sprite
        nframes = this->getAnimationHandler()->numberOfStaticFrames();
        for (int i = 0; i < nframes; i++) {
            auto *frame = dynamic_cast<HealthBarObjectStaticFrame*>(this->getAnimationHandler()->getStaticFrame(i));
            if (frame != nullptr) {
                auto &sprite = frame->getSprite();
                sprite.setPosition({SPACE + SPRITE_WIDTH * i + SPACE * i, SPACE});
                if (value > 0 && value > i) {
                    sprite.setTextureRect({0, (int)SPRITE_HEIGHT, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
                } else {
                    sprite.setTextureRect({(int)SPRITE_WIDTH*2, (int)SPRITE_HEIGHT, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
                }
            }
        }
    }
}

HealthBarObject::HealthBarObjectStaticFrame::HealthBarObjectStaticFrame(Game *game) : StaticFrame(game) {
    std::string rpath = "./resources/Hud.png";
    this->loadTextureFromFile(rpath);

    this->sprite = new sf::Sprite();
    this->sprite->setTexture(*this->getTexture());
}

HealthBarObject::HealthBarObjectStaticFrame::HealthBarObjectStaticFrame(const HealthBarObjectStaticFrame &original) : StaticFrame(
        original) {
    this->sprite = new sf::Sprite(*original.sprite);
}

HealthBarObject::HealthBarObjectStaticFrame::~HealthBarObjectStaticFrame() {
    delete this->sprite;
    this->sprite = nullptr;
}

HealthBarObject::HealthBarObjectStaticFrame &HealthBarObject::HealthBarObjectStaticFrame::operator=(const HealthBarObject::HealthBarObjectStaticFrame &original) {
    if (this != &original) {
        this->sprite = new sf::Sprite(*original.sprite);
    }
    return *this;
}

HealthBarObject::HealthBarObjectStaticFrame *HealthBarObject::HealthBarObjectStaticFrame::clone() const {
    return new HealthBarObjectStaticFrame(*this);
}

void HealthBarObject::HealthBarObjectStaticFrame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(*this->sprite);
}

sf::Sprite &HealthBarObject::HealthBarObjectStaticFrame::getSprite() const {
    return *this->sprite;
}
