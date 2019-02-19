//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_ISCENE_HPP
#define ALIENADVENTURE_ISCENE_HPP

class IGame;
class ObjectHandler;

#include <SFML/System/Clock.hpp>

#include <memory>

class IScene {
private:
    IGame* m_game;

    std::shared_ptr<ObjectHandler> m_objectHandler;

    bool m_initialized;

    bool m_paused;

    sf::Clock m_elapsedClock;

    float m_elapsedTime;

    sf::Clock m_pausedClock;

    float m_pausedTime;

    IScene(const IScene &original);

    IScene& operator=(const IScene &original);
protected:
    virtual void performInit() = 0;

    virtual void performDeinit() = 0;

    virtual void processExtraEvents() = 0;

    virtual void performExtraUpdates(const float dt) = 0;

    virtual void performExtraDrawing() = 0;

    virtual void didPause() = 0;

    virtual void didResume() = 0;
public:
    explicit IScene(IGame* game);

    virtual ~IScene() = 0;

    IGame* getGame() const;

    void init();

    void deinit();

    void processEvents();

    void update(const float dt);

    void draw();

    virtual void cleanup() = 0;

    ObjectHandler& getObjectHandler() const;

    bool isInitialized() const;

    void pause();

    void resume();

    bool isPaused() const;

    float getElapsedTime() const;

    float getPausedTime() const;
};

#endif //ALIENADVENTURE_ISCENE_HPP
