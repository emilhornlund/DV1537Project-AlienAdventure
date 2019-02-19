/**
 * @file EventHandler.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <SFML/Window/Keyboard.hpp>

#include <vector>

namespace sf {
    class RenderWindow;
}

class EventHandler {
public:
    struct KeyStatus {
        bool pressed, released, down;
    };

    struct WindowStatus {
        bool closed, resized, lostFocus, gainedFocus, mouseInWindow, hasFocus;
    };
private:
    sf::RenderWindow* m_window;

    std::vector<KeyStatus> m_keyStatus;

    WindowStatus m_windowStatus;

    void resetKeyStatus();

    EventHandler(const EventHandler &original);

    EventHandler& operator=(const EventHandler &original);
public:
    explicit EventHandler(sf::RenderWindow& window);

    ~EventHandler();

    void updateEvents();

    const WindowStatus &getWindowStatus() const;

    const KeyStatus &getKeyStatus(const sf::Keyboard::Key &key) const;
};

#endif /* EventHandler_h */
