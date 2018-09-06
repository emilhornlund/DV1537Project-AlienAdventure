/**
 * @file LevelHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <fstream>
#include <sstream>

#include "Background.hpp"
#include "Camera.hpp"
#include "CollectibleCoin.hpp"
#include "CollectibleHealth.hpp"
#include "EnemyBee.hpp"
#include "EnemyBeeBlack.hpp"
#include "EnemyFishBlue.hpp"
#include "EnemyFishGreen.hpp"
#include "EnemyFishPink.hpp"
#include "EnemyFrog.hpp"
#include "EnemyMouse.hpp"
#include "EnemySlimeBlue.hpp"
#include "EnemySlimeGreen.hpp"
#include "EnemySlimePurple.hpp"
#include "EnemySnail.hpp"
#include "EnemySnailMushroom.hpp"
#include "EnemyWormGreen.hpp"
#include "EnemyWormPink.hpp"
#include "Game.hpp"
#include "HealthBarObject.hpp"
#include "LevelHandler.hpp"
#include "ObjectHandler.hpp"
#include "Player.hpp"
#include "PropertyHandler.hpp"
#include "TileMap.hpp"
#include "WindowHandler.hpp"
#include "World.hpp"

LevelHandler::LevelHandler(Game* game) {
    this->game = game;
    this->worldSize = {0, 0};
}

LevelHandler::~LevelHandler() = default;

sf::Vector2i LevelHandler::getWorldSize() const {
    return this->worldSize;
}

unsigned int LevelHandler::readNextInt(std::ifstream &file) const {
    unsigned int input = 0;
    file >> input;
    file.ignore();
    return input;
}

std::string LevelHandler::readNextString(std::ifstream &file) const {
    std::string input;
    std::getline(file, input);
    return input;
}

void LevelHandler::load() {
    std::string rpath = "./resources/Level.txt";

    std::ifstream inFile;
    inFile.open(rpath);

    int worldWidth = this->readNextInt(inFile);
    int worldHeight = this->readNextInt(inFile);
    this->worldSize = { worldWidth, worldHeight };

    this->game->getRenderer()->getCamera().setGlobalBounds({0, 0, (float)worldWidth, (float)worldHeight});

    World* world = new World(this->game, {worldWidth/70, worldHeight/70}, {70, 70});
    this->game->getObjectHandler()->addObject(world);

    int nrOfBackgrounds = this->readNextInt(inFile);
    Background* background = new Background(this->game);
    for (int i = 0; i < nrOfBackgrounds; i++) {
        unsigned int column = this->readNextInt(inFile);
        unsigned int row = this->readNextInt(inFile);
        unsigned int times = this->readNextInt(inFile);
        for (int j = 0; j < times; j++) {
            background->addBackgroundSequence(column, row);
        }
    }
    world->addBackground(background);

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

        TileMap* tileMap = new TileMap(this->game); //TODO: fixa en getGame
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

    auto *player = new Player(this->game, playerSpawnAreas, playerExitArea);
    this->game->getObjectHandler()->addObject(player);

    int nrOfEnemies = this->readNextInt(inFile);
    for (int i = 0; i < nrOfEnemies; i++) {
        std::string typeString = this->readNextString(inFile);
        sf::IntRect spawnArea;
        spawnArea.left = this->readNextInt(inFile);
        spawnArea.top = this->readNextInt(inFile);
        spawnArea.width = this->readNextInt(inFile);
        spawnArea.height = this->readNextInt(inFile);

        if (typeString == "Bee") {
            auto *enemy = new EnemyBee(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "BeeBlack") {
            auto *enemy = new EnemyBeeBlack(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "SlimeBlue") {
            auto *enemy = new EnemySlimeBlue(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "SlimeGreen") {
            auto *enemy = new EnemySlimeGreen(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "SlimePurple") {
            auto *enemy = new EnemySlimePurple(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "Snail") {
            auto *enemy = new EnemySnail(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "SnailMushroom") {
            auto *enemy = new EnemySnailMushroom(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "WormGreen") {
            auto *enemy = new EnemyWormGreen(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
        } else if (typeString == "WormPink") {
            auto *enemy = new EnemyWormPink(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(enemy);
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
            auto coin = new CollectibleCoin(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(coin);
        } else if (typeString == "Health") {
            auto health = new CollectibleHealth(this->game, spawnArea);
            this->game->getObjectHandler()->addObject(health);
        } else {
            throw std::runtime_error("Unknown collectible type: " + typeString);
        }
    }

    auto *healthBarObject = new HealthBarObject(this->game);
    this->game->getObjectHandler()->addObject(healthBarObject);

    this->game->getPropertyHandler()->set<unsigned int>("health", 3);

    inFile.close();
}

