//
// Created by Emil Hörnlund on 2019-02-19.
//

#include <Core/Tileset.hpp>

#include <tinyxml2.h>

CGL::Tileset::Tileset(const std::string &name, const std::string &source, const int firstGID,
                      const sf::Vector2i &tileSize,
                      const unsigned int spacing, const unsigned int tileCount, const unsigned int columns) : m_name(name), m_source(source),
                                                                                                              m_firstGID(firstGID), m_tileSize(tileSize), m_spacing(spacing), m_tileCount(tileCount),
                                                                                                              m_columns(columns) {}

CGL::Tileset::Tileset(const tinyxml2::XMLElement *node) {
    if (node == nullptr)
        throw "Failed to initialize tileset";

    auto imageNode = node->FirstChildElement("image");
    if (imageNode == nullptr)
        throw "Failed to parse image node";
    this->m_source = imageNode->Attribute("source");

    this->m_name = node->Attribute("name");
    this->m_firstGID = node->IntAttribute("firstgid");

    const auto tileWidth = node->IntAttribute("tilewidth");
    const auto tileHeight = node->IntAttribute("tileheight");
    this->m_tileSize = sf::Vector2i(tileWidth, tileHeight);

    this->m_spacing = node->UnsignedAttribute("spacing");
    this->m_tileCount = node->UnsignedAttribute("tilecount");
    this->m_columns = node->UnsignedAttribute("columns");
    this->m_rows = this->m_columns > 0 ? this->m_tileCount / this->m_columns : 0;
}

std::string CGL::Tileset::getName() const {
    return this->m_name;
}

std::string CGL::Tileset::getSource() const {
    return this->m_source;
}

int CGL::Tileset::getFirstGID() const {
    return this->m_firstGID;
}

sf::Vector2i CGL::Tileset::getTileSize() const {
    return this->m_tileSize;
}

unsigned int CGL::Tileset::getSpacing() const {
    return this->m_spacing;
}

unsigned int CGL::Tileset::getTileCount() const {
    return this->m_tileCount;
}

unsigned int CGL::Tileset::getColumns() const {
    return this->m_columns;
}

unsigned int CGL::Tileset::getRows() const {
    return this->m_rows;
}
