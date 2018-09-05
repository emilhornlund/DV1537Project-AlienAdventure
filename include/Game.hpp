/**
 * @file Game.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Core.hpp"

enum class GameState { Playing, Paused, Respawn, GameOver };

class Game {
private:
    bool running;

    int exitCode;

    sf::Clock gameClock;

    GameState state;

    ImageResourceHandler *imageResourceHandler;

    MusicResourceHandler *musicResourceHandler;

    TextureResourceHandler *textureResourceHandler;

    SoundBufferResourceHandler *soundBufferResourceHandler;

    Renderer *render;

    EventHandler *eventHandler;

    ObjectHandler *objectHandler;

    LevelHandler *levelHandler;

    Hud* hud;

    Menu* pauseMenu;

    Menu* respawnMenu;

    Menu* gameOverMenu;

    sf::Music* backgroundMusic;

    sf::SoundBuffer* clickSoundBuffer;

    sf::Sound* clickSound;

    void update();

    void draw();
public:
    Game();

    ~Game();

    int run();

    bool isRunning() const;

    void setState(const GameState state);

    GameState getState() const;

    ImageResourceHandler* getImageResourceHandler() const;

    MusicResourceHandler* getMusicResourceHandler() const;

    TextureResourceHandler* getTextureResourceHandler() const;

    SoundBufferResourceHandler *getSoundBufferResourceHandler() const;

    Renderer* getRenderer() const;

    EventHandler* getEventHandler() const;

    ObjectHandler* getObjectHandler() const;

    LevelHandler* getLevelHandler() const;

    Hud* getHud() const;

    Menu* getPauseMenu() const;

    Menu* getRespawnMenu() const;

    Menu* getGameOverMenu() const;
};

#endif /* Game_hpp */
