/**
 * @file LevelHandler.cpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <fstream>
#include <sstream>

#include "LevelHandler.hpp"
#include "ObjectHandler.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Collectible.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include "TileMap.hpp"

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

    Player* player = new Player(this->game, playerSpawnAreas, playerExitArea);
    this->game->getObjectHandler()->addObject(player);

    int nrOfEnemies = this->readNextInt(inFile);
    for (int i = 0; i < nrOfEnemies; i++) {
        std::string typeString = this->readNextString(inFile);
        sf::IntRect spawnArea;
        spawnArea.left = this->readNextInt(inFile);
        spawnArea.top = this->readNextInt(inFile);
        spawnArea.width = this->readNextInt(inFile);
        spawnArea.height = this->readNextInt(inFile);

        Enemy::EnemyType type;
        if (typeString == "SlimePurple") {
            type = Enemy::EnemyType::SlimePurple;
        } else if (typeString == "SlimeGreen") {
            type = Enemy::EnemyType::SlimeGreen;
        } else if (typeString == "SlimeBlue") {
            type = Enemy::EnemyType::SlimeBlue;
        } else if (typeString == "Bee") {
            type = Enemy::EnemyType::Bee;
        } else if (typeString == "BeeBlack") {
            type = Enemy::EnemyType::BeeBlack;
        } else if (typeString == "Snail") {
            type = Enemy::EnemyType::Snail;
        } else if (typeString == "SnailMushroom") {
            type = Enemy::EnemyType::SnailMushroom;
        } else if (typeString == "WormGreen") {
            type = Enemy::EnemyType::WormGreen;
        } else if (typeString == "WormPink") {
            type = Enemy::EnemyType::WormPink;
        } else {
            throw std::runtime_error("Unknown enemy type: " + typeString);
        }

        Enemy* enemy = new Enemy(this->game, spawnArea, type);
        this->game->getObjectHandler()->addObject(enemy);
    }

    int nrOfCollectables = this->readNextInt(inFile);
    for (int i = 0; i < nrOfCollectables; i++) {
        std::string typeString = this->readNextString(inFile);
        sf::IntRect spawnArea;
        spawnArea.left = this->readNextInt(inFile);
        spawnArea.top = this->readNextInt(inFile);
        spawnArea.width = this->readNextInt(inFile);
        spawnArea.height = this->readNextInt(inFile);

        Collectible::CollectibleType type;
        if (typeString == "CoinGold") {
            type = Collectible::CollectibleType::GoldCoin;
        } else if (typeString == "Life") {
            type = Collectible::CollectibleType::Life;
        } else {
            throw std::runtime_error("Unknown collectible type: " + typeString);
        }

        Collectible* collectible = new Collectible(this->game, spawnArea, type);
        this->game->getObjectHandler()->addObject(collectible);
    }

    inFile.close();
}

