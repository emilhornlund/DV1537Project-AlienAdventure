/**
 * @file EventHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */


#include "../../include/classes/EventHandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

EventHandler::EventHandler(sf::RenderWindow& window) : m_window(&window) {
    this->m_windowStatus.closed = false;
    this->m_windowStatus.resized = false;
    this->m_windowStatus.lostFocus = false;
    this->m_windowStatus.gainedFocus = false;
    this->m_windowStatus.mouseInWindow = true;
    this->m_windowStatus.hasFocus = true;

    this->m_keyStatus.resize(sf::Keyboard::KeyCount);
    this->resetKeyStatus();
}

EventHandler::~EventHandler() = default;

void EventHandler::resetKeyStatus() {
    for (auto& object : this->m_keyStatus) {
        object.pressed = false;
        object.released = false;
        object.down = false;
    }
}

void EventHandler::updateEvents() {
    sf::Event event{};

    this->m_windowStatus.closed = false;
    this->m_windowStatus.resized = false;
    this->m_windowStatus.lostFocus = false;
    this->m_windowStatus.gainedFocus = false;

    for (auto& object : this->m_keyStatus) {
        object.pressed = false;
        object.released = false;
    }

    while (this->m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->m_windowStatus.closed = true;
                break;
            case sf::Event::Resized:
                this->m_windowStatus.resized = true;
                break;
            case sf::Event::LostFocus:
                this->m_windowStatus.lostFocus = true;
                break;
            case sf::Event::GainedFocus:
                this->m_windowStatus.gainedFocus = true;
                break;
            case sf::Event::KeyPressed:
                m_keyStatus[event.key.code].pressed = true;
                m_keyStatus[event.key.code].down = true;
                break;
            case sf::Event::KeyReleased:
                m_keyStatus[event.key.code].released = true;
                m_keyStatus[event.key.code].down = false;
                break;
            default:
                break;
        }
    }
}

const EventHandler::WindowStatus &EventHandler::getWindowStatus() const {
    return this->m_windowStatus;
}

const EventHandler::KeyStatus &EventHandler::getKeyStatus(const sf::Keyboard::Key &key) const {
    return this->m_keyStatus[key];
}
