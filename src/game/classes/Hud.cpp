//
// Created by Emil Hörnlund on 2018-09-08.
//

#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/SpriteEntity.hpp"
#include "core/interfaces/IGame.hpp"
#include "game/classes/Hud.hpp"

#include <SFML/Graphics/Texture.hpp>

const float SPRITE_WIDTH = 52.0;
const float SPRITE_HEIGHT = 48.0;

const float SPACING = 10.0;
const float FACTOR = 0.8f;

Hud::Hud(IGame *game) : IGameObject(game, IGameObject::DRAW_ORDER_HUD, false),
                        m_currentHealth(0),
                        m_currentCoins(0),
                        m_coinSprite(nullptr) {}

Hud::~Hud() = default;

void Hud::restore(const bool respawn) {
    this->m_currentHealth = 0;
    this->m_currentCoins = 0;

    if (!respawn) {
        ///reset entities
        this->clearEntities();
        this->m_healthSprites.clear();
        this->m_coinDigitSprites.clear();
        this->m_coinSprite = nullptr;
        this->m_coinDigitSprites.clear();
        this->m_coinMultiplierSprite = nullptr;

        ///setup coins
        this->setupCoin();
        this->setupCoinInitialDigit();
        this->setupCoinMultiplier();
    }
}

void Hud::processEvents() {

}

void Hud::update(const float dt) {
    if (this->getGame()->getPropertyHandler().hasProperty("health")) {
        auto value = this->getGame()->getPropertyHandler().get<unsigned int>("health");
        if (this->m_currentHealth != value) {
            this->updateHealth(value);
        }
    }
    if (this->getGame()->getPropertyHandler().hasProperty("coins")) {
        auto value = this->getGame()->getPropertyHandler().get<unsigned int>("coins");
        if (this->m_currentCoins != value) {
            this->updateCoins(value);
        }
    }
}

void Hud::updateHealth(const unsigned health) {
    ///assign and process the new health only if it has changed.
    if (this->m_currentHealth == health) {
        return;
    }
    this->m_currentHealth = health;

    ///add extra health sprites if needed
    if (health > this->m_healthSprites.size()) {
        auto n = health - this->m_healthSprites.size();
        for (int i = 0; i < n; i++) {
            std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
            const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Hud.png");
            entity->setTexture(texture);
            entity->setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
            this->addEntity(entity);
            this->m_healthSprites.push_back(entity);
        }
    }

    ///reconfigure each health sprite
    for (unsigned long i = 0; i < this->m_healthSprites.size(); i++) {
        auto entity = this->m_healthSprites.at(i);
        if (health > 0 && health > i) {
            entity->setTextureRect({0, (int)SPRITE_HEIGHT, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
        } else {
            entity->setTextureRect({(int)SPRITE_WIDTH*2, (int)SPRITE_HEIGHT, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT});
        }
        entity->setOffset(SPRITE_WIDTH/2+SPACING+(i*SPRITE_WIDTH)+(i*SPACING), SPRITE_HEIGHT/2+SPACING);
    }
}

void Hud::updateCoins(const unsigned coins) {
    ///assign and process the new number of collected coins only if it has changed.
    if (this->m_currentCoins == coins) {
        return;
    }
    this->m_currentCoins = coins;

    ///add extra coin digit sprites if needed
    unsigned int n = (int)std::to_string(coins).size();
    if (n > this->m_coinDigitSprites.size()) {
        auto j = n - this->m_coinDigitSprites.size();
        for (int i = 0; i < j; i++) {
            std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
            const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Hud.png");
            entity->setTexture(texture);
            entity->setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
            this->addEntity(entity);
            this->m_coinDigitSprites.push_back(entity);
        }
    }

    ///reconfigure each health sprite
    if (this->m_coinDigitSprites.size() == n) {
        for (unsigned long i = 0; i < this->m_coinDigitSprites.size(); i++) {
            auto entity = this->m_coinDigitSprites.at(i);
            int digit = std::to_string(coins)[n-i-1] - '0';
            entity->setTextureRect({ (int)SPRITE_WIDTH*(digit+1), (int)SPRITE_HEIGHT*3, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT });
            entity->setOffset(800 - (SPRITE_WIDTH/2)*3 - SPACING - (SPRITE_WIDTH*FACTOR*i), SPRITE_HEIGHT/2+SPACING);
        }
    }

    ///update the offset for the coin multiplier
    const auto minOffset = this->m_coinDigitSprites.at(this->m_coinDigitSprites.size()-1)->getOffset().x;
    this->m_coinMultiplierSprite->setOffset(minOffset - SPRITE_WIDTH*FACTOR, SPRITE_HEIGHT/2+SPACING);
}

void Hud::setupCoin() {
    std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Hud.png");
    entity->setTexture(texture);
    entity->setTextureRect({ (int)SPRITE_WIDTH*3, (int)SPRITE_HEIGHT, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT });
    entity->setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
    entity->setOffset(800 - (SPRITE_WIDTH/2) - SPACING, SPRITE_HEIGHT/2+SPACING);
    this->addEntity(entity);
    this->m_coinSprite = entity;
}

void Hud::setupCoinInitialDigit() {
    std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Hud.png");
    entity->setTexture(texture);
    entity->setTextureRect({ (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT*3, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT });
    entity->setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
    entity->setOffset(800 - (SPRITE_WIDTH/2)*3 - SPACING, SPRITE_HEIGHT/2+SPACING);
    this->addEntity(entity);
    this->m_coinDigitSprites.push_back(entity);
}

void Hud::setupCoinMultiplier() {
    std::shared_ptr<SpriteEntity> entity = std::make_shared<SpriteEntity>();
    const auto& texture = this->getGame()->getTextureResourceHandler().load("resources/Hud.png");
    entity->setTexture(texture);
    entity->setTextureRect({ 0, (int)SPRITE_HEIGHT*3, (int)SPRITE_WIDTH, (int)SPRITE_HEIGHT });
    entity->setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
    const auto minOffset = this->m_coinDigitSprites.at(this->m_coinDigitSprites.size()-1)->getOffset().x;
    entity->setOffset(minOffset - SPRITE_WIDTH*FACTOR, SPRITE_HEIGHT/2+SPACING);
    this->addEntity(entity);
    this->m_coinMultiplierSprite = entity;
}
