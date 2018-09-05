/**
 * @file EventHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class EventHandler {
public:
    struct KeyStatus {
        bool pressed, released, down;
    };

    struct WindowStatus {
        bool closed, resized, lostFocus, gainedFocus, mouseInWindow, hasFocus;
    };
private:
    sf::RenderWindow *window;

    KeyStatus* keyStatus;

    WindowStatus windowStatus;

    void resetKeyStatus();
public:
    explicit EventHandler(sf::RenderWindow& window);

    ~EventHandler();

    void updateEvents();

    const WindowStatus &getWindowStatus() const;

    const KeyStatus &getKeyStatus(const sf::Keyboard::Key key) const;
};

#endif /* EventHandler_h */
