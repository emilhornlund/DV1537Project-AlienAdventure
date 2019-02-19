//
// Created by Emil Hörnlund on 2018-09-07.
//

#ifndef ALIENADVENTURE_IGAME_HPP
#define ALIENADVENTURE_IGAME_HPP

#include <string>
#include <memory>

#include <SFML/System/Clock.hpp>

class PropertyHandler;
class WindowHandler;
class EventHandler;
class SceneHandler;
class IMenuObject;
class Level;

template <typename Resource>
class ResourceHandler;

namespace sf {
    class Image;
    class Music;
    class SoundBuffer;
    class Texture;
}

class IGame {
private:
    std::shared_ptr<ResourceHandler<sf::Image>> m_imageResourceHandler;

    std::shared_ptr<ResourceHandler<sf::Music>> m_musicResourceHandler;

    std::shared_ptr<ResourceHandler<sf::SoundBuffer>> m_soundBufferResourceHandler;

    std::shared_ptr<ResourceHandler<sf::Texture>> m_textureResourceHandler;

    std::shared_ptr<ResourceHandler<Level>> m_levelResourceHandler;

    std::shared_ptr<PropertyHandler> m_propertyHandler;

    std::shared_ptr<WindowHandler> m_windowHandler;

    std::shared_ptr<EventHandler> m_eventHandler;

    std::shared_ptr<SceneHandler> m_sceneHandler;

    std::shared_ptr<IMenuObject> m_menu;

    bool m_running;

    int m_exitCode;

    sf::Clock m_gameClock;

    IGame(const IGame &original);

    IGame& operator=(const IGame &original);
public:
    IGame(const unsigned int windowWidth, const unsigned int windowHeight, const std::string& title);

    virtual ~IGame() = 0;

    int run();

    bool isRunning() const;

    void quit(const int exitCode);

    void setMenu(std::shared_ptr<IMenuObject> menu);

    bool hasActiveMenu() const;

    void closeMenu();

    PropertyHandler& getPropertyHandler() const;

    ResourceHandler<sf::Image>& getImageResourceHandler() const;

    ResourceHandler<sf::Music>& getMusicResourceHandler() const;

    ResourceHandler<sf::SoundBuffer>& getSoundBufferResourceHandler() const;

    ResourceHandler<sf::Texture>& getTextureResourceHandler() const;

    ResourceHandler<Level>& getLevelResourceHandler() const;

    WindowHandler& getWindowHandler() const;

    EventHandler& getEventHandler() const;

    SceneHandler& getSceneHandler() const;
};

#endif //ALIENADVENTURE_IGAME_HPP
