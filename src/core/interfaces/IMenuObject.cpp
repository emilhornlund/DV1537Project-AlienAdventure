//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "core/classes/EventHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/SpriteEntity.hpp"
#include "core/classes/WindowHandler.hpp"
#include "core/interfaces/IGame.hpp"
#include "core/interfaces/IMenuObject.hpp"
#include "game/classes/GameScene.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

const float ITEM_SPACING = 20.f;

IMenuObject::IMenuObject(IGame *game) : IGameObject(game, GameScene::DRAW_ORDER_MENU, false), m_selectedItemIndex(0), m_hasPendingSelection(false) {
    this->m_clickSound = std::make_shared<sf::Sound>();
    this->m_clickSound->setBuffer(game->getSoundBufferResourceHandler().load("./resources/Click.wav"));

    this->m_switchSound = std::make_shared<sf::Sound>();
    this->m_switchSound->setBuffer(game->getSoundBufferResourceHandler().load("./resources/Switch.wav"));
}

IMenuObject::~IMenuObject() = default;

void IMenuObject::addItem(const sf::IntRect& unselectedTextureRect, const sf::IntRect& selectedTextureRect, const sf::Texture& texture) {
    auto menuItem = std::make_shared<MenuItem>();
    menuItem->unselectedTextureRect = unselectedTextureRect;
    menuItem->selectedTextureRect = selectedTextureRect;
    menuItem->m_entity = std::make_shared<SpriteEntity>();
    menuItem->m_entity->setTexture(texture);
    menuItem->m_entity->setTextureRect((this->m_menuItems.empty() ? selectedTextureRect : unselectedTextureRect));
    menuItem->m_entity->setOrigin((float)unselectedTextureRect.width/2, (float)unselectedTextureRect.height/2);
    this->addEntity(menuItem->m_entity);
    this->m_menuItems.push_back(menuItem);
    this->updateOffsets();
}

void IMenuObject::toggleNext() {
    this->m_selectedItemIndex = static_cast<int>((this->m_selectedItemIndex + 1) % this->m_menuItems.size());
}

void IMenuObject::togglePrevious() {
    this->m_selectedItemIndex = static_cast<int>((this->m_selectedItemIndex ? this->m_selectedItemIndex : this->m_menuItems.size()) - 1);
}

void IMenuObject::restore(const bool respawn) {
    this->m_selectedItemIndex = 0;
    this->m_hasPendingSelection = false;
    this->m_selectionClock.restart();
    for (unsigned long i = 0; i < this->m_menuItems.size(); i++) {
        auto menuItem = this->m_menuItems.at(i);
        if (i == this->m_selectedItemIndex) {
            menuItem->m_entity->setTextureRect(menuItem->selectedTextureRect);
        } else {
            menuItem->m_entity->setTextureRect(menuItem->unselectedTextureRect);
        }
    }
}

void IMenuObject::processEvents() {
    bool upPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Up).pressed;
    bool downPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Down).pressed;
    bool returnPressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Return).pressed;

    if (returnPressed) {
        this->m_clickSound->play();
        this->m_selectionClock.restart();
        this->m_hasPendingSelection = true;
    } else if (upPressed != downPressed) {
        this->m_menuItems.at((unsigned long)this->m_selectedItemIndex)->m_entity->setTextureRect(this->m_menuItems.at((unsigned long)this->m_selectedItemIndex)->unselectedTextureRect);
        if (upPressed) {
            this->togglePrevious();
        }
        if (downPressed) {
            this->toggleNext();
        }
        this->m_switchSound->play();
        this->m_menuItems.at((unsigned long)this->m_selectedItemIndex)->m_entity->setTextureRect(this->m_menuItems.at((unsigned long)this->m_selectedItemIndex)->selectedTextureRect);
    }
}

void IMenuObject::updateOffsets() {
    float totalHeight = 0.0f;
    for (unsigned long i = 0; i < this->m_menuItems.size(); i++) {
        const auto menuItem = this->m_menuItems.at(i);
        if (this->m_selectedItemIndex == i) {
            totalHeight += menuItem->selectedTextureRect.height;
        } else {
            totalHeight += menuItem->unselectedTextureRect.height;
        }
    }

    if (!this->m_menuItems.empty()) {
        totalHeight += ITEM_SPACING * (this->m_menuItems.size()-1);
    }

    const auto windowSize = this->getGame()->getWindowHandler().getWindowSize();
    const auto startY = (windowSize.y - totalHeight) / 2.f;

    for (unsigned long i = 0; i < this->m_menuItems.size(); i++) {
        auto menuItem = this->m_menuItems.at(i);
        sf::Vector2f offset;
        if (this->m_selectedItemIndex == i) {
            offset.x = windowSize.x/2.f;
            offset.y = startY + (float)menuItem->selectedTextureRect.height/2 + (float)menuItem->selectedTextureRect.height*i + ITEM_SPACING*i;
        } else {
            offset.x = windowSize.x/2.f;
            offset.y = startY + (float)menuItem->unselectedTextureRect.height/2 + (float)menuItem->unselectedTextureRect.height*i + ITEM_SPACING*i;
        }
        menuItem->m_entity->setOffset(offset);
    }
}

int IMenuObject::getSelectedItemIndex() const {
    return (this->m_hasPendingSelection && this->m_selectionClock.getElapsedTime().asSeconds() > 0.1) ? this->m_selectedItemIndex : -1;
}
