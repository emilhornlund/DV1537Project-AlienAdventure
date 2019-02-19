//
// Created by Emil Hörnlund on 2018-09-14.
//

#include <Core/Camera.hpp>
#include <Core/EventHandler.hpp>
#include <Core/Level.hpp>
#include <Core/ObjectHandler.hpp>
#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SceneHandler.hpp>
#include <Core/WindowHandler.hpp>
#include <Core/Tilelayer.hpp>
#include <Core/Tileset.hpp>

#include <Game/Cloud.hpp>
#include <Game/CollectibleCoin.hpp>
#include <Game/CollectibleHealth.hpp>
#include <Game/EnemyBee.hpp>
#include <Game/EnemyBeeBlack.hpp>
#include <Game/EnemySlimeBlue.hpp>
#include <Game/EnemySlimeGreen.hpp>
#include <Game/EnemySlimePurple.hpp>
#include <Game/EnemySnail.hpp>
#include <Game/EnemySnailMushroom.hpp>
#include <Game/EnemyWormGreen.hpp>
#include <Game/EnemyWormPink.hpp>
#include <Game/Game.hpp>
#include <Game/GameOverMenuObject.hpp>
#include <Game/GameScene.hpp>
#include <Game/Hud.hpp>
#include <Game/LevelCompleteMenuObject.hpp>
#include <Game/ParallaxBackground.hpp>
#include <Game/PauseMenuObject.hpp>
#include <Game/Player.hpp>
#include <Game/Sun.hpp>
#include <Game/TileMap.hpp>
#include <Game/World.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Window/Keyboard.hpp>

AA::GameScene::GameScene(CGL::IGame *game, const std::string &levelFilePath) : IScene(game), m_levelFilePath(levelFilePath) {}

AA::GameScene::~GameScene() = default;

void AA::GameScene::performInit() {
    auto& level = this->getGame()->getLevelResourceHandler().load(this->m_levelFilePath);

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
    auto worldSize = sf::Vector2i((level.getMapSize().x * level.getTileSize().x), (level.getMapSize().y * level.getTileSize().y));
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
    const auto tiles = sf::Vector2i(worldSize.x/level.getTileSize().x, worldSize.y/level.getTileSize().y);
    auto world = std::make_shared<World>(this->getGame(), tiles, level.getTileSize());
    this->getObjectHandler().addObject(world);

    int tilemapIdx = 0;
    const auto &tilelayers = level.getTilelayers();
    for (const auto &tilelayer : tilelayers) {
        const auto usedTilesets = level.getUsedTilesets(tilelayer);
        for (const auto &tileset : usedTilesets) {
            const auto data = level.getTileData(tilelayer, tileset);
            auto tilemap = std::make_shared<TileMap>(this->getGame());
            tilemap->setName(tilelayer->getName());
            tilemap->setColumns(static_cast<const unsigned int>(tilelayer->getLayerSize().x));
            tilemap->setRows(static_cast<const unsigned int>(tilelayer->getLayerSize().y));
            tilemap->setTileWidth(static_cast<const unsigned int>(tileset->getTileSize().x));
            tilemap->setTileHeight(static_cast<const unsigned int>(tileset->getTileSize().y));
            tilemap->setTilesetColumns(tileset->getColumns());
            tilemap->setTilesetRows(tileset->getRows());
            tilemap->setFilename(tileset->getSource());
            tilemap->setData(data);
            world->addTileMap(tilemap, tilemapIdx);
            tilemapIdx++;
        }
    }

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
    std::vector<sf::IntRect> playerSpawnAreas = {{280, 0, 70, 630}, {2660, 70, 70, 630}};

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

void AA::GameScene::performDeinit() {
    this->m_backgroundMusic->stop();
}

void AA::GameScene::cleanup() {

}

void AA::GameScene::processExtraEvents() {
    bool escapePressed = this->getGame()->getEventHandler().getKeyStatus(sf::Keyboard::Key::Escape).pressed;
    bool lostFocus = this->getGame()->getEventHandler().getWindowStatus().lostFocus;
    if ((escapePressed || lostFocus) && !this->getGame()->hasActiveMenu()) {
        this->pause();
        this->getGame()->setMenu(this->m_pauseMenu);
    }
}

void AA::GameScene::performExtraUpdates(const float dt) {
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

void AA::GameScene::performExtraDrawing() {

}

void AA::GameScene::didPause() {

}

void AA::GameScene::didResume() {

}
