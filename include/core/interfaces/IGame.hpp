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
class ObjectHandler;
class Menu;

template <typename Resource>
class ResourceHandler;

namespace sf {
    class Image;
    class Music;
    class SoundBuffer;
    class Texture;
    class Sound;
}

class IGame {
public:
    enum class GameState { Uninitialized, Playing, Paused, Respawn, GameOver };
private:
    std::shared_ptr<ResourceHandler<sf::Image>> imageResourceHandler;

    std::shared_ptr<ResourceHandler<sf::Music>> musicResourceHandler;

    std::shared_ptr<ResourceHandler<sf::SoundBuffer>> soundBufferResourceHandler;

    std::shared_ptr<ResourceHandler<sf::Texture>> textureResourceHandler;

    std::shared_ptr<PropertyHandler> propertyHandler;

    std::shared_ptr<WindowHandler> windowHandler;

    std::shared_ptr<EventHandler> eventHandler;

    std::shared_ptr<ObjectHandler> objectHandler;

    bool running;

    int exitCode;

    GameState state;

    sf::Clock gameClock;

    std::shared_ptr<Menu> pauseMenu;

    std::shared_ptr<Menu> respawnMenu;

    std::shared_ptr<Menu> gameOverMenu;

    sf::Music* backgroundMusic;

    std::shared_ptr<sf::Sound> clickSound;

    IGame(const IGame &original);

    IGame& operator=(const IGame &original);

    void update();

    void draw();
public:
    IGame(const unsigned int windowWidth, const unsigned int windowHeight, const std::string& title);

    virtual ~IGame() = 0;

    int run();

    bool isRunning() const;

    void quit(const int exitCode);

    void setState(const GameState state);

    GameState getState() const;

    PropertyHandler& getPropertyHandler() const;

    ResourceHandler<sf::Image>& getImageResourceHandler() const;

    ResourceHandler<sf::Music>& getMusicResourceHandler() const;

    ResourceHandler<sf::SoundBuffer>& getSoundBufferResourceHandler() const;

    ResourceHandler<sf::Texture>& getTextureResourceHandler() const;

    WindowHandler& getWindowHandler() const;

    EventHandler& getEventHandler() const;

    ObjectHandler& getObjectHandler() const;

    Menu& getPauseMenu() const;

    Menu& getRespawnMenu() const;

    Menu& getGameOverMenu() const;

    virtual void loadLevel() = 0;
};

#endif //ALIENADVENTURE_IGAME_HPP
