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
#include <Core/IGameObject.hpp>

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

    std::vector<sf::IntRect> playerSpawns = {};
    sf::IntRect playerExit = {};

    const auto& objectGroups = level.getObjectGroups();
    for (const auto &objectGroup : objectGroups) {
        for (const auto &object : objectGroup->objects) {
            const auto rect = sf::IntRect(object->position.x, object->position.y, object->size.x, object->size.y);
            if (objectGroup->name == "Player") {
                if (object->type == "Spawn" && object->name == "Spawn") {
                    playerSpawns.push_back(rect);
                } else if (object->type == "Exit" && object->name == "Exit") {
                    playerExit = rect;
                }
            } else if (objectGroup->name == "Objects") {
                if (object->type == "Enemy") {
                    if (object->name == "Bee") {
                        this->getObjectHandler().addObject(std::make_shared<EnemyBee>(this->getGame(), rect));
                    } else if (object->name == "BeeBlack") {
                        this->getObjectHandler().addObject(std::make_shared<EnemyBeeBlack>(this->getGame(), rect));
                    } else if (object->name == "SlimeBlue") {
                        this->getObjectHandler().addObject(std::make_shared<EnemySlimeBlue>(this->getGame(), rect));
                    } else if (object->name == "SlimeGreen") {
                        this->getObjectHandler().addObject(std::make_shared<EnemySlimeGreen>(this->getGame(), rect));
                    } else if (object->name == "SlimePurple") {
                        this->getObjectHandler().addObject(std::make_shared<EnemySlimePurple>(this->getGame(), rect));
                    } else if (object->name == "Snail") {
                        this->getObjectHandler().addObject(std::make_shared<EnemySnail>(this->getGame(), rect));
                    } else if (object->name == "SnailMushroom") {
                        this->getObjectHandler().addObject(std::make_shared<EnemySnailMushroom>(this->getGame(), rect));
                    } else if (object->name == "WormGreen") {
                        this->getObjectHandler().addObject(std::make_shared<EnemyWormGreen>(this->getGame(), rect));
                    } else if (object->name == "WormPink") {
                        this->getObjectHandler().addObject(std::make_shared<EnemyWormPink>(this->getGame(), rect));
                    }
                } else if (object->type == "Collectible") {
                    if (object->name == "CoinGold") {
                        this->getObjectHandler().addObject(std::make_shared<CollectibleCoin>(this->getGame(), rect));
                    } else if (object->name == "Life") {
                        this->getObjectHandler().addObject(std::make_shared<CollectibleHealth>(this->getGame(), rect));
                    }
                }
            }
        }
    }

    ///TODO: sort the player spawn points by horizontal x values

    ///setup the player
    auto player = std::make_shared<Player>(this->getGame(), playerSpawns, playerExit);
    this->getObjectHandler().addObject(player);

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
