//
// Created by Emil Hörnlund on 2018-09-14.
//

#include "core/classes/Camera.hpp"
#include "core/classes/EventHandler.hpp"
#include "core/classes/Level.hpp"
#include "core/classes/ObjectHandler.hpp"
#include "core/classes/PropertyHandler.hpp"
#include "core/classes/ResourceHandler.hpp"
#include "core/classes/SceneHandler.hpp"
#include "core/classes/WindowHandler.hpp"
#include "game/classes/Cloud.hpp"
#include "game/classes/CollectibleCoin.hpp"
#include "game/classes/CollectibleHealth.hpp"
#include "game/classes/EnemyBee.hpp"
#include "game/classes/EnemyBeeBlack.hpp"
#include "game/classes/EnemySlimeBlue.hpp"
#include "game/classes/EnemySlimeGreen.hpp"
#include "game/classes/EnemySlimePurple.hpp"
#include "game/classes/EnemySnail.hpp"
#include "game/classes/EnemySnailMushroom.hpp"
#include "game/classes/EnemyWormGreen.hpp"
#include "game/classes/EnemyWormPink.hpp"
#include "game/classes/Game.hpp"
#include "game/classes/GameOverMenuObject.hpp"
#include "game/classes/GameScene.hpp"
#include "game/classes/Hud.hpp"
#include "game/classes/LevelCompleteMenuObject.hpp"
#include "game/classes/ParallaxBackground.hpp"
#include "game/classes/PauseMenuObject.hpp"
#include "game/classes/Player.hpp"
#include "game/classes/Sun.hpp"
#include "game/classes/TileMap.hpp"
#include "game/classes/World.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Window/Keyboard.hpp>

GameScene::GameScene(IGame *game, const std::string &levelFilePath) : IScene(game), m_levelFilePath(levelFilePath) {}

GameScene::~GameScene() = default;

void GameScene::performInit() {

    auto& level = this->getGame()->getLevelResourceHandler().load("level_test.tmx");

    ///setup the background music
    this->m_backgroundMusic = &this->getGame()->getMusicResourceHandler().open("Music.ogg");
    this->m_backgroundMusic->setLoop(true);
    this->m_backgroundMusic->setVolume(50);
    this->m_backgroundMusic->play();

    ///setup the menus
    this->m_pauseMenu = std::make_shared<PauseMenuObject>(this->getGame());
    this->m_gameOverMenu = std::make_shared<GameOverMenuObject>(this->getGame());
    this->m_levelCompleteMenu = std::make_shared<LevelCompleteMenuObject>(this->getGame());

    ///determine the world size
    auto worldSize = sf::Vector2i(6160, 840);
    this->getGame()->getPropertyHandler().set<sf::Vector2i>("worldSize", worldSize);
    this->getGame()->getWindowHandler().getCamera().setGlobalBounds({0, 0, (float)worldSize.x, (float)worldSize.y});

    ///reset the players health and collected coins
    this->getGame()->getPropertyHandler().set<unsigned int>("health", 3);
    this->getGame()->getPropertyHandler().set<unsigned int>("coins", 0);

    ///setup the hud objects
    auto hud = std::make_shared<Hud>(this->getGame());
    this->getObjectHandler().addObject(hud);

    ///setup the parallax background
    auto parallaxBackground = std::make_shared<ParallaxBackground>(this->getGame());
    this->getObjectHandler().addObject(parallaxBackground);

    ///setup the world object
    const auto tileSize = sf::Vector2i(70, 70);
    const auto tiles = sf::Vector2i(worldSize.x/tileSize.x, worldSize.y/tileSize.y);
    auto world = std::make_shared<World>(this->getGame(), tiles, tileSize);
    this->getObjectHandler().addObject(world);

    ///setup the ground tilemap
    auto groundTileMap = std::make_shared<TileMap>(this->getGame());
    groundTileMap->setName("Ground");
    groundTileMap->setColumns(88);
    groundTileMap->setRows(12);
    groundTileMap->setTileWidth(70);
    groundTileMap->setTileHeight(70);
    groundTileMap->setTilesetColumns(9);
    groundTileMap->setTilesetRows(12);
    groundTileMap->setFilename("Grounds.png");
    groundTileMap->setData({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,0,0,0,37,0,0,0,37,0,0,0,0,0,38,39,39,40,0,0,37,0,0,0,0,0,38,39,39,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,38,40,0,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,38,39,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,38,39,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,48,39,39,49,0,0,0,0,0,0,39,39,39,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,41,41,0,0,0,46,39,39,39,41,41,41,0,0,0,0,0,0,0,0,0,0,39,39,47,0,0,0,0,0,0,0,0,0,39,39,39,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,3,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,3,3,3,3,3,3,3,3,3,3,3,0,0,0,41,41,0,0,0,0,41,41,41,41,41,41,0,0,0,0,39,39,39,39,39,39,41,41,0,0,0,0,0,0,39,39,39,39,41,41,41,0,0,0,3,3,3,3,3,0,0,0,3,3,0,0,0,0,5,5,5,5,5,0,0,0,0,3,3,0,0,0,3,3,0,0,0,0,5,5,5,5,5,5,5,5,5,5,5});
    world->addTileMap(groundTileMap, 0);

    ///setup the misc tilemap
    auto miscTileMap = std::make_shared<TileMap>(this->getGame());
    miscTileMap->setName("Misc");
    miscTileMap->setColumns(88);
    miscTileMap->setRows(12);
    miscTileMap->setTileWidth(70);
    miscTileMap->setTileHeight(70);
    miscTileMap->setTilesetColumns(9);
    miscTileMap->setTilesetRows(12);
    miscTileMap->setFilename("Misc.png");
    miscTileMap->setData({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,78,8,0,0,0,0,0,0,0,0,28,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,35,0,0,36,76,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,28,28,0,0,0,0,0,0,0,0,0,8,28,29,0,0,0,0,0,0,0,0,28,28,29,0,0,0,0,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,4,4,4,0,0,4,4,4,4,0,0,0,0,0,4,4,4,4,0,0,4,4,4,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0});
    world->addTileMap(miscTileMap, 1);

    ///setup sun
    auto sun = std::make_shared<Sun>(this->getGame());
    this->getObjectHandler().addObject(sun);

    ///setup clouds
    auto cw = 400;
    auto ch = 200;
    auto xn = (int)worldSize.x/cw;
    auto yn = (int)worldSize.y/ch;
    for (int i = 0; i < xn; i++) {
        auto x = i*cw;
        for (int j = 0; j < yn; j++) {
            auto y = -(int)this->getGame()->getWindowHandler().getWindowSize().y/2+j*ch;
            auto r = sf::IntRect(x, y, cw, ch);
            auto cloud = std::make_shared<Cloud>(this->getGame(), r);
            this->getObjectHandler().addObject(cloud);
        }
    }

    ///set the possible player spawn areas
    std::vector<sf::IntRect> playerSpawnAreas = {
            {280, 0, 70, 630},
            {2660, 70, 70, 630}
    };

    ///set the player exit area
    auto playerExitArea = sf::IntRect({6020, 0, 70, 700});

    ///setup the player
    auto player = std::make_shared<Player>(this->getGame(), playerSpawnAreas, playerExitArea);
    this->getObjectHandler().addObject(player);

    ///setup enemies
    this->getObjectHandler().addObject(std::make_shared<EnemySnail>(this->getGame(), sf::IntRect(1330, 700, 420, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemySlimeGreen>(this->getGame(), sf::IntRect(1120, 210, 280, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemyWormGreen>(this->getGame(), sf::IntRect(1960, 210, 280, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemyWormPink>(this->getGame(), sf::IntRect(560, 630, 280, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBee>(this->getGame(), sf::IntRect(1260, 420, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBee>(this->getGame(), sf::IntRect(560, 70, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBee>(this->getGame(), sf::IntRect(1680, 280, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBee>(this->getGame(), sf::IntRect(2240, 490, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBeeBlack>(this->getGame(), sf::IntRect(3430, 490, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBeeBlack>(this->getGame(), sf::IntRect(3780, 490, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBeeBlack>(this->getGame(), sf::IntRect(5180, 490, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemyBeeBlack>(this->getGame(), sf::IntRect(4830, 490, 70, 280)));
    this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), sf::IntRect(3010, 700, 350, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), sf::IntRect(3220, 210, 280, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), sf::IntRect(4060, 560, 350, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), sf::IntRect(4760, 350, 210, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), sf::IntRect(5390, 630, 280, 70)));
    this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), sf::IntRect(5670, 630, 280, 70)));

    ///setup coin collectibles
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(910, 560, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(490, 490, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(2450, 350, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(980, 350, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(700, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(420, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(140, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(1680, 70, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(2030, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(1470, 490, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(2870, 280, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(3150, 420, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(3640, 350, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(3780, 630, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(3430, 630, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(5180, 630, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(4480, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(4130, 280, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(4830, 630, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(5180, 280, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(5180, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(4830, 560, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(4200, 490, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), sf::IntRect(4200, 560, 70, 70)));

    ///setup health collectibles
    this->getObjectHandler().addObject(std::make_shared<CollectibleHealth>(this->getGame(), sf::IntRect(1260, 210, 70, 70)));
    this->getObjectHandler().addObject(std::make_shared<CollectibleHealth>(this->getGame(), sf::IntRect(3080, 210, 70, 70)));

    this->getObjectHandler().restoreObjects(false);
}

void GameScene::performDeinit() {
    this->m_backgroundMusic->stop();
}

void GameScene::cleanup() {

}

void GameScene::processExtraEvents() {
    bool escapePressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Escape).pressed;
    bool lostFocus = this->getGame()->getEventHandler().getWindowStatus().lostFocus;
    if ((escapePressed || lostFocus) && !this->getGame()->hasActiveMenu()) {
        this->pause();
        this->getGame()->setMenu(this->m_pauseMenu);
    }
}

void GameScene::performExtraUpdates(const float dt) {
    auto gameOver = this->getGame()->getPropertyHandler().get<bool>("gameOver");
    auto levelComplete = this->getGame()->getPropertyHandler().get<bool>("levelComplete");
    if (gameOver != levelComplete && !this->getGame()->hasActiveMenu()) {
        if (gameOver) {
            this->getGame()->setMenu(this->m_gameOverMenu);
        }
        if (levelComplete) {
            this->getGame()->setMenu(this->m_levelCompleteMenu);
        }
    }
}

void GameScene::performExtraDrawing() {

}

void GameScene::didPause() {

}

void GameScene::didResume() {

}
