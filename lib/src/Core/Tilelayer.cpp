//
// Created by Emil Hörnlund on 2019-02-19.
//

#include <Core/Tilelayer.hpp>

#include <sstream>
#include <tinyxml2.h>

CGL::Tilelayer::Tilelayer(const std::string &name, const sf::Vector2i &layerSize) : m_name(name), m_layerSize(layerSize) {}

CGL::Tilelayer::Tilelayer(const tinyxml2::XMLElement *node) {
    if (node == nullptr)
        throw "Failed to initialize tilelayer";

    this->m_name = node->Attribute("name");

    const auto layerWidth = node->IntAttribute("width");
    const auto layerHeight = node->IntAttribute("height");
    this->m_layerSize = sf::Vector2i(layerWidth, layerHeight);

    if (!this->parseTileData(node->FirstChildElement("data")))
        throw "Failed to parse tiledata";
}

bool CGL::Tilelayer::parseTileData(const tinyxml2::XMLElement *node) {
    if (node == nullptr)
        return false;

    const auto encoding = node->Attribute("encoding");
    if (encoding == nullptr || strncmp(encoding, "csv", 3) != 0)
        return false;

    const auto text = node->GetText();
    if (text == nullptr)
        return false;

    std::stringstream ss(text);
    int i;
    while (ss >> i) {
        this->m_tiles.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return true;
}

std::string CGL::Tilelayer::getName() const {
    return this->m_name;
}

sf::Vector2i CGL::Tilelayer::getLayerSize() const {
    return this->m_layerSize;
}

const std::vector<int> &CGL::Tilelayer::getTiles() const {
    return this->m_tiles;
}

int CGL::Tilelayer::getTile(const int x, const int y) const {
    if (x < 0 || x >= this->m_layerSize.x || y < 0 || y >= this->m_layerSize.y)
        return 0;
    auto tile = this->m_tiles[x + y * this->m_layerSize.x];
    return tile;
}
