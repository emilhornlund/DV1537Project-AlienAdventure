//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_GAMESCENE_HPP
#define ALIENADVENTURE_GAMESCENE_HPP

#include "../../../lib/include/interfaces/IScene.hpp"

#include <string>

class PauseMenuObject;
class GameOverMenuObject;
class LevelCompleteMenuObject;

namespace sf {
    class Music;
}

class GameScene : public IScene {
public:
    static const int DRAW_ORDER_MENU = 0;
    static const int DRAW_ORDER_HUD = 1;
    static const int DRAW_ORDER_ENEMY_DEAD = 2;
    static const int DRAW_ORDER_PLAYER = 3;
    static const int DRAW_ORDER_ENEMY_ALIVE = 4;
    static const int DRAW_ORDER_COLLECTIBLE = 5;
    static const int DRAW_ORDER_CLOUD_LAYER1 = 6;
    static const int DRAW_ORDER_TILEMAP = 7;
    static const int DRAW_ORDER_CLOUD_LAYER2 = 8;
    static const int DRAW_ORDER_BACKGROUND = 9;
    static const int DRAW_ORDER_SUN = 10;
private:
    const std::string m_levelFilePath;

    sf::Music* m_backgroundMusic;

    std::shared_ptr<PauseMenuObject> m_pauseMenu;

    std::shared_ptr<GameOverMenuObject> m_gameOverMenu;

    std::shared_ptr<LevelCompleteMenuObject> m_levelCompleteMenu;

    GameScene(const GameScene &original);

    GameScene& operator=(const GameScene &original);
protected:
    void performInit() override;

    void performDeinit() override;

    void processExtraEvents() override;

    void performExtraUpdates(const float dt) override;

    void performExtraDrawing() override;

    void didPause() override;

    void didResume() override;
public:
    GameScene(IGame *game, const std::string &levelFilePath);

    ~GameScene() override;

    void cleanup() override;
};


#endif //ALIENADVENTURE_GAMESCENE_HPP
