/**
 * @file Game.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "core/classes/Camera.hpp"
#include "core/classes/ObjectHandler.hpp"
#include "core/classes/PropertyHandler.hpp"
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
#include "game/classes/Hud.hpp"
#include "game/classes/ParallaxBackground.hpp"
#include "game/classes/Player.hpp"
#include "game/classes/Sun.hpp"
#include "game/classes/TileMap.hpp"
#include "game/classes/World.hpp"

#include <fstream>
#include <sstream>
#include <memory>

Game::Game() : IGame(800, 600, "Alien Adventure") {}

Game::~Game() = default;

unsigned int Game::readNextInt(std::ifstream &file) const {
    unsigned int input = 0;
    file >> input;
    file.ignore();
    return input;
}

std::string Game::readNextString(std::ifstream &file) const {
    std::string input;
    std::getline(file, input);
    return input;
}

void Game::loadLevel() {
    std::string rpath = "./resources/Level.txt";

    std::ifstream inFile;
    inFile.open(rpath);

    int worldWidth = this->readNextInt(inFile);
    int worldHeight = this->readNextInt(inFile);

    this->getPropertyHandler().set<sf::Vector2i>("worldSize", {worldWidth, worldHeight});
    this->getWindowHandler().getCamera().setGlobalBounds({0, 0, (float)worldWidth, (float)worldHeight});

    const auto tiles = sf::Vector2i(worldWidth/70, worldHeight/70);
    const auto tileSize = sf::Vector2i(70, 70);
    auto world = std::make_shared<World>(this, tiles, tileSize);
    this->getObjectHandler().addObject(world);

    auto parallaxBackground = std::make_shared<ParallaxBackground>(this);
    this->getObjectHandler().addObject(parallaxBackground);

    int nrOfTileMaps = this->readNextInt(inFile);
    for (int i = 0; i < nrOfTileMaps; i++) {
        std::string name = this->readNextString(inFile);
        unsigned int columns = this->readNextInt(inFile);
        unsigned int rows = this->readNextInt(inFile);
        unsigned int tileWidth = this->readNextInt(inFile);
        unsigned int tileHeight = this->readNextInt(inFile);
        unsigned int tilesetColumns = this->readNextInt(inFile);
        unsigned int tilesetRows = this->readNextInt(inFile);
        std::string filename = this->readNextString(inFile);

        std::string dataString = this->readNextString(inFile);
        std::stringstream ss(dataString);
        std::vector<int> data;
        int j;
        while (ss >> j) {
            data.push_back(j);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }

        auto tileMap = std::make_shared<TileMap>(this);
        tileMap->setName(name);
        tileMap->setColumns(columns);
        tileMap->setRows(rows);
        tileMap->setTileWidth(tileWidth);
        tileMap->setTileHeight(tileHeight);
        tileMap->setTilesetColumns(tilesetColumns);
        tileMap->setTilesetRows(tilesetRows);
        tileMap->setFilename(filename);
        tileMap->setData(data);
        world->addTileMap(tileMap, i);
    }


    int nrOfPlayerSpawnAreas = this->readNextInt(inFile);
    std::vector<sf::IntRect> playerSpawnAreas;

    for (int i = 0; i < nrOfPlayerSpawnAreas; i++) {
        sf::IntRect playerSpawnArea;
        playerSpawnArea.left = this->readNextInt(inFile);
        playerSpawnArea.top = this->readNextInt(inFile);
        playerSpawnArea.width = this->readNextInt(inFile);
        playerSpawnArea.height = this->readNextInt(inFile);
        playerSpawnAreas.push_back(playerSpawnArea);
    }

    sf::IntRect playerExitArea;
    playerExitArea.left = this->readNextInt(inFile);
    playerExitArea.top = this->readNextInt(inFile);
    playerExitArea.width = this->readNextInt(inFile);
    playerExitArea.height = this->readNextInt(inFile);

    auto player = std::make_shared<Player>(this, playerSpawnAreas, playerExitArea);
    this->getObjectHandler().addObject(player);

    int nrOfEnemies = this->readNextInt(inFile);
    for (int i = 0; i < nrOfEnemies; i++) {
        std::string typeString = this->readNextString(inFile);
        sf::IntRect spawnArea;
        spawnArea.left = this->readNextInt(inFile);
        spawnArea.top = this->readNextInt(inFile);
        spawnArea.width = this->readNextInt(inFile);
        spawnArea.height = this->readNextInt(inFile);

        if (typeString == "Bee") {
            auto enemy = std::make_shared<EnemyBee>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "BeeBlack") {
            auto enemy = std::make_shared<EnemyBeeBlack>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "SlimeBlue") {
            auto enemy = std::make_shared<EnemySlimeBlue>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "SlimeGreen") {
            auto enemy = std::make_shared<EnemySlimeGreen>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "SlimePurple") {
            auto enemy = std::make_shared<EnemySlimePurple>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "Snail") {
            auto enemy = std::make_shared<EnemySnail>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "SnailMushroom") {
            auto enemy = std::make_shared<EnemySnailMushroom>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "WormGreen") {
            auto enemy = std::make_shared<EnemyWormGreen>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else if (typeString == "WormPink") {
            auto enemy = std::make_shared<EnemyWormPink>(this, spawnArea);
            this->getObjectHandler().addObject(enemy);
        } else {
            throw std::runtime_error("Unknown enemy type: " + typeString);
        }
    }

    int nrOfCollectables = this->readNextInt(inFile);
    for (int i = 0; i < nrOfCollectables; i++) {
        std::string typeString = this->readNextString(inFile);
        sf::IntRect spawnArea;
        spawnArea.left = this->readNextInt(inFile);
        spawnArea.top = this->readNextInt(inFile);
        spawnArea.width = this->readNextInt(inFile);
        spawnArea.height = this->readNextInt(inFile);

        if (typeString == "CoinGold") {
            auto coin = std::make_shared<CollectibleCoin>(this, spawnArea);
            this->getObjectHandler().addObject(coin);
        } else if (typeString == "Health") {
            auto health = std::make_shared<CollectibleHealth>(this, spawnArea);
            this->getObjectHandler().addObject(health);
        } else {
            throw std::runtime_error("Unknown collectible type: " + typeString);
        }
    }

    this->getPropertyHandler().set<unsigned int>("health", 3);
    this->getPropertyHandler().set<unsigned int>("coins", 0);

    auto hud = std::make_shared<Hud>(this);
    this->getObjectHandler().addObject(hud);

    auto sun = std::make_shared<Sun>(this);
    this->getObjectHandler().addObject(sun);

    auto cw = 400;
    auto ch = 200;
    auto xn = (int)worldWidth/cw;
    auto yn = (int)worldHeight/ch;
    for (int i = 0; i < xn; i++) {
        auto x = i*cw;
        for (int j = 0; j < yn; j++) {
            auto y = -(int)this->getWindowHandler().getWindowSize().y/2+j*ch;
            auto r = sf::IntRect(x, y, cw, ch);
            auto cloud = std::make_shared<Cloud>(this, r);
            this->getObjectHandler().addObject(cloud);
        }
    }

    inFile.close();
}
