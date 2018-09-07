/**
 * @file Game.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System/Clock.hpp>

#include "Core.hpp"

class Game {
public:
    enum class GameState { Uninitialized, Playing, Paused, Respawn, GameOver };
private:
    bool running;

    int exitCode;

    sf::Clock gameClock;

    GameState state;

    PropertyHandler *propertyHandler;

    ImageResourceHandler *imageResourceHandler;

    MusicResourceHandler *musicResourceHandler;

    TextureResourceHandler *textureResourceHandler;

    SoundBufferResourceHandler *soundBufferResourceHandler;

    WindowHandler *windowHandler;

    EventHandler *eventHandler;

    ObjectHandler *objectHandler;

    LevelHandler *levelHandler;

    Menu* pauseMenu;

    Menu* respawnMenu;

    Menu* gameOverMenu;

    sf::Music* backgroundMusic;

    sf::SoundBuffer* clickSoundBuffer;

    sf::Sound* clickSound;

    Game(const Game &original);

    Game& operator=(const Game &original);

    void update();

    void draw();
public:
    Game();

    ~Game();

    int run();

    bool isRunning() const;

    void quit(const int exitCode);

    void setState(const GameState state);

    GameState getState() const;

    ImageResourceHandler* getImageResourceHandler() const;

    MusicResourceHandler* getMusicResourceHandler() const;

    TextureResourceHandler* getTextureResourceHandler() const;

    SoundBufferResourceHandler *getSoundBufferResourceHandler() const;

    PropertyHandler* getPropertyHandler() const;

    WindowHandler* getWindowHandler() const;

    EventHandler* getEventHandler() const;

    ObjectHandler* getObjectHandler() const;

    LevelHandler* getLevelHandler() const;

    Menu* getPauseMenu() const;

    Menu* getRespawnMenu() const;

    Menu* getGameOverMenu() const;
};

#endif /* Game_hpp */
