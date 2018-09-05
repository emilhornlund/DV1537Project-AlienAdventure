/**
 * @file TileMap.cpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#include "TileMap.hpp"

TileMap::TileMap() = default;

TileMap::TileMap(const TileMap &original) : StaticFrame(original) {
    this->name = original.getName();
    this->columns = original.getColumns();
    this->rows = original.getRows();
    this->tileWidth = original.getTileWidth();
    this->tileHeight = original.getTileHeight();
    this->tilesetColumns = original.getTilesetColumns();
    this->tilesetRows = original.getTilesetRows();
    this->filename = original.getFilename();
    this->data = original.getData();
    this->vertices = original.vertices;
}

TileMap::~TileMap() = default;

TileMap& TileMap::operator=(const TileMap &original) {
    if (this != &original) {
        this->name = original.getName();
        this->columns = original.getColumns();
        this->rows = original.getRows();
        this->tileWidth = original.getTileWidth();
        this->tileHeight = original.getTileHeight();
        this->tilesetColumns = original.getTilesetColumns();
        this->tilesetRows = original.getTilesetRows();
        this->filename = original.getFilename();
        this->data = original.getData();
        this->vertices = original.vertices;
    }
    return *this;
}

std::string TileMap::getName() const {
    return this->name;
}

unsigned int TileMap::getColumns() const {
    return this->columns;
}

unsigned int TileMap::getRows() const {
    return this->rows;
}

unsigned int TileMap::getTileWidth() const {
    return this->tileWidth;
}

unsigned int TileMap::getTileHeight() const {
    return this->tileHeight;
}

unsigned int TileMap::getTilesetColumns() const {
    return this->tilesetColumns;
}

unsigned int TileMap::getTilesetRows() const {
    return this->tilesetRows;
}

std::string TileMap::getFilename() const {
    return this->filename;
}

std::vector<int> TileMap::getData() const {
    return this->data;
}

void TileMap::setName(const std::string &name) {
    this->name = name;
}

void TileMap::setColumns(const unsigned int columns) {
    this->columns = columns;
}

void TileMap::setRows(const unsigned int rows) {
    this->rows = rows;
}

void TileMap::setTileWidth(const unsigned int tileWidth) {
    this->tileWidth = tileWidth;
}

void TileMap::setTileHeight(const unsigned int tileHeight) {
    this->tileHeight = tileHeight;
}

void TileMap::setTilesetColumns(const unsigned int tilesetColumns) {
    this->tilesetColumns = tilesetColumns;
}

void TileMap::setTilesetRows(const unsigned int tilesetRows) {
    this->tilesetRows = tilesetRows;
}

void TileMap::setFilename(const std::string &filename) {
    this->filename = filename;
}

void TileMap::setData(const std::vector<int> data) {
    this->data.clear();
    this->data = data;
}

void TileMap::generate() {
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(this->columns * this->rows * 4);

    sf::Vector2u tileSize = { this->tileWidth, this->tileHeight };

    for (unsigned int i = 0; i < this->columns; ++i) {
        for (unsigned int j = 0; j < this->rows; ++j) {
            int dataNr = this->data[i + j * this->columns];

            if (dataNr > 0) {
                int index = dataNr - 1;

                int tu = index % (this->getTexture()->getSize().x / tileSize.x);
                int tv = index / (this->getTexture()->getSize().x / tileSize.x);

                sf::Vertex* quad = &this->vertices[(i + j * this->columns) * 4];

                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
    }
}

TileMap* TileMap::clone() const {
    return new TileMap(*this);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = this->getTexture();
    target.draw(this->vertices, states);
}
