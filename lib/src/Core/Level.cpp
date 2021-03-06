//
// Created by Emil Hörnlund on 2018-09-15.
//

#include <Core/Level.hpp>
#include <Core/Tileset.hpp>
#include <Core/Tilelayer.hpp>

#include <tinyxml2.h>
#include <iostream>

bool CGL::Level::loadFromFile(const std::string &filename) {
    ///load the xml document from disk
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename.c_str());

    ///parse the first map node
    const auto mapNode = doc.FirstChildElement("map");
    if (mapNode == nullptr)
        return false;

    ///grab the size of all tiles
    const auto tileWidth = mapNode->IntAttribute("tilewidth");
    const auto tileHeight = mapNode->IntAttribute("tileheight");
    this->m_tileSize = {tileWidth, tileHeight};

    ///grab the number of tiles (x,y) e.g. mapSize
    const auto mapWidth = mapNode->IntAttribute("width");
    const auto mapHeight = mapNode->IntAttribute("height");
    this->m_mapSize = {mapWidth, mapHeight};

    ///parse tilesets
    if (!this->parseTilesets(mapNode))
        return false;

    ///parse tilelayers
    if (!this->parseTilelayers(mapNode))
        return false;

    ///parse objects
    return this->parseObjectGroups(mapNode);
}

bool CGL::Level::parseTilesets(const tinyxml2::XMLElement *node) {
    if (node == nullptr)
        return false;
    auto tilesetNode = node->FirstChildElement("tileset");
    while (tilesetNode != nullptr) {
        try {
            const auto tileset = std::make_shared<const Tileset>(tilesetNode);
            this->m_tilesets.push_back(tileset);
        } catch (...) {
            return false;
        }
        tilesetNode = tilesetNode->NextSiblingElement("tileset");
    }
    return true;
}

bool CGL::Level::parseTilelayers(const tinyxml2::XMLElement *node) {
    if (node == nullptr)
        return false;
    auto layerNode = node->FirstChildElement("layer");
    while (layerNode != nullptr) {
        try {
            const auto tilelayer = std::make_shared<const Tilelayer>(layerNode);
            this->m_tilelayers.push_back(tilelayer);
        } catch (...) {
            return false;
        }
        layerNode = layerNode->NextSiblingElement("layer");
    }
    return true;
}

bool CGL::Level::parseObjectGroups(const tinyxml2::XMLElement *node) {
    if (node == nullptr)
        return false;
    auto objectGroupNode = node->FirstChildElement("objectgroup");
    while (objectGroupNode != nullptr) {
        auto id = objectGroupNode->UnsignedAttribute("id");

        auto name = objectGroupNode->Attribute("name");

        const auto objects = this->parseObjects(objectGroupNode);

        const auto objectGroup = std::make_shared<const ObjectGroup>(id, name, objects);
        this->m_objectGroups.push_back(objectGroup);

        objectGroupNode = objectGroupNode->NextSiblingElement("objectgroup");
    }
    return true;
}

const std::vector<std::shared_ptr<const CGL::Object>> CGL::Level::parseObjects(const tinyxml2::XMLElement *node) {
    std::vector<std::shared_ptr<const Object>> objects;
    if (node != nullptr) {
        auto objectNode = node->FirstChildElement("object");
        while (objectNode != nullptr) {
            auto id = objectNode->UnsignedAttribute("id");

            auto name = objectNode->Attribute("name");

            auto type = objectNode->Attribute("type");

            auto posX = objectNode->IntAttribute("x");
            auto posY = objectNode->IntAttribute("y");
            auto position = sf::Vector2i(posX, posY);

            auto sizeX = objectNode->IntAttribute("width");
            auto sizeY = objectNode->IntAttribute("height");
            auto size = sf::Vector2i(sizeX, sizeY);

            auto object = std::make_shared<const Object>(id, name, type, position, size);
            objects.push_back(object);
            objectNode = objectNode->NextSiblingElement("object");
        }
    }
    return objects;
}

sf::Vector2i CGL::Level::getTileSize() const {
    return this->m_tileSize;
}

sf::Vector2i CGL::Level::getMapSize() const {
    return this->m_mapSize;
}

const std::vector<CGL::TilesetPtr> &CGL::Level::getTilesets() const {
    return this->m_tilesets;
}

const std::vector<CGL::TilelayerPtr> &CGL::Level::getTilelayers() const {
    return this->m_tilelayers;
}

const std::vector<CGL::ObjectGroupPtr> &CGL::Level::getObjectGroups() const {
    return this->m_objectGroups;
}

const std::vector<CGL::TilesetPtr> CGL::Level::getUsedTilesets(CGL::TilelayerPtr tilelayerPtr) const {
    std::vector<TilesetPtr> usedTilesets;
    auto maxID = std::numeric_limits<std::uint32_t>::max();
    for (auto it = this->m_tilesets.rbegin(); it != this->m_tilesets.rend(); ++it) {
        for (const auto& tile : tilelayerPtr->getTiles()) {
            if (tile >= (*it)->getFirstGID() && tile < maxID) {
                usedTilesets.push_back((*it));
                break;
            }
        }
        maxID = static_cast<unsigned int>((*it)->getFirstGID());
    }
    return usedTilesets;
}

const std::vector<int> CGL::Level::getTileData(CGL::TilelayerPtr tilelayerPtr, CGL::TilesetPtr tilesetPtr) const {
    std::vector<int> data;
    for (const auto& tile : tilelayerPtr->getTiles()) {
        auto id = (tile >= tilesetPtr->getFirstGID()) ? tile - tilesetPtr->getFirstGID() : -1; ///TODO check upperbound
        data.push_back(id);
    }
    return data;
}
