//
// Created by Emil Hörnlund on 2018-09-15.
//

#include <Core/classes/Level.hpp>

#include <iostream>
#include <sstream>

Level::Level() = default;

Level::~Level() = default;

bool Level::loadFromFile(const std::string &filename) {
    tinyxml2::XMLDocument xmlDoc;
    auto eResult = xmlDoc.LoadFile(filename.c_str());
    if (eResult != tinyxml2::XML_SUCCESS) {
        return false;
    }
    auto pRoot = xmlDoc.FirstChildElement("map");
    if (pRoot == nullptr) {
        return false;
    }
    this->parseMap(pRoot);
    return true;
}

const sf::Vector2i &Level::getNumberOfTiles() const {
    return this->m_tiles;
}

const sf::Vector2i &Level::getTileSize() const {
    return this->m_tileSize;
}

const sf::Vector2i &Level::getMapSize() const {
    return this->m_mapSize;
}

void Level::parseMap(const tinyxml2::XMLElement *root) {
    root->FindAttribute("width")->QueryIntValue(&this->m_tiles.x);
    root->FindAttribute("height")->QueryIntValue(&this->m_tiles.y);

    root->FindAttribute("tilewidth")->QueryIntValue(&this->m_tileSize.x);
    root->FindAttribute("tileheight")->QueryIntValue(&this->m_tileSize.y);

    this->m_mapSize.x = this->m_tiles.x * this->m_tileSize.x;
    this->m_mapSize.y = this->m_tiles.y * this->m_tileSize.y;

    const tinyxml2::XMLNode* node = root->FirstChild();
    while (node != nullptr) {
        const auto element = node->ToElement();
        const auto name = std::string(element->Name());
        if (name == "tileset") {
            this->parseTileset(element);
        } else if (name == "layer") {
            this->parseLayer(element);
        }
        node = node->NextSibling();
    }
}

void Level::parseTileset(const tinyxml2::XMLElement *element) {
    Tileset tileset;
    tileset.name = element->Attribute("name");
    element->FindAttribute("firstgid")->QueryIntValue(&tileset.firstgid);
    element->FindAttribute("tilewidth")->QueryIntValue(&tileset.tileSize.x);
    element->FindAttribute("tileheight")->QueryIntValue(&tileset.tileSize.y);
    element->FindAttribute("tilecount")->QueryIntValue(&tileset.tilecount);
    element->FindAttribute("columns")->QueryIntValue(&tileset.columns);
    const tinyxml2::XMLElement* imageElement = element->FirstChild()->ToElement();
    if (imageElement != nullptr && std::string(imageElement->Name()) == "image") {
        tileset.image.source = imageElement->Attribute("source");
        imageElement->FindAttribute("width")->QueryIntValue(&tileset.image.size.x);
        imageElement->FindAttribute("height")->QueryIntValue(&tileset.image.size.y);
    }
    this->m_tilesets.push_back(tileset);
}

void Level::parseLayer(const tinyxml2::XMLElement *element) {
    Layer layer;
    layer.name = element->Attribute("name");
    element->FindAttribute("width")->QueryIntValue(&layer.size.x);
    element->FindAttribute("height")->QueryIntValue(&layer.size.y);
    const std::string data = element->FirstChild()->ToElement()->GetText();
    std::stringstream ss(data);
    int i;
    while (ss >> i) {
        layer.data.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    this->m_layers.push_back(layer);
}

const std::vector<Level::Tileset> &Level::getTilesets() const {
    return this->m_tilesets;
}

const std::vector<Level::Layer> &Level::getLayers() const {
    return this->m_layers;
}
