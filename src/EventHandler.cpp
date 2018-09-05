/**
 * @file EventHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */


#include "EventHandler.hpp"

EventHandler::EventHandler(sf::RenderWindow& window) {
    this->window = &window;

    this->windowStatus.closed = false;
    this->windowStatus.resized = false;
    this->windowStatus.lostFocus = false;
    this->windowStatus.gainedFocus = false;
    this->windowStatus.mouseInWindow = true;
    this->windowStatus.hasFocus = true;

    this->keyStatus = new KeyStatus[sf::Keyboard::KeyCount];
    this->resetKeyStatus();
}

EventHandler::~EventHandler() {
    delete[] this->keyStatus;
    this->keyStatus = nullptr;
}

void EventHandler::resetKeyStatus() {
    for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
        this->keyStatus[i].pressed = false;
        this->keyStatus[i].released = false;
        this->keyStatus[i].down = false;
    }
}

void EventHandler::updateEvents() {
    sf::Event event{};

    this->windowStatus.closed = false;
    this->windowStatus.resized = false;
    this->windowStatus.lostFocus = false;
    this->windowStatus.gainedFocus = false;

    for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
        this->keyStatus[i].pressed = false;
        this->keyStatus[i].released = false;
        //this->keyStatus[i].down = false; ///TODO: Kolla om detta är korrekt
    }

    while (this->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->windowStatus.closed = true;
                break;
            case sf::Event::Resized:
                this->windowStatus.resized = true;
                break;
            case sf::Event::LostFocus:
                this->windowStatus.lostFocus = true;
                break;
            case sf::Event::GainedFocus:
                this->windowStatus.gainedFocus = true;
                break;
            case sf::Event::KeyPressed:
                keyStatus[event.key.code].pressed = true;
                keyStatus[event.key.code].down = true;
                break;
            case sf::Event::KeyReleased:
                keyStatus[event.key.code].released = true;
                keyStatus[event.key.code].down = false;
                break;
            default:
                break;
        }
    }
}

const EventHandler::WindowStatus &EventHandler::getWindowStatus() const {
    return this->windowStatus;
}

const EventHandler::KeyStatus &EventHandler::getKeyStatus(const sf::Keyboard::Key key) const {
    return this->keyStatus[key];
}
