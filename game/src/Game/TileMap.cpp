/**
 * @file TileMap.cpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#include <Game/TileMap.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

AA::TileMap::TileMap(CGL::IGame* game) : IEntity() {}

AA::TileMap::~TileMap() = default;

std::string AA::TileMap::getName() const {
    return this->name;
}

unsigned int AA::TileMap::getColumns() const {
    return this->columns;
}

unsigned int AA::TileMap::getRows() const {
    return this->rows;
}

unsigned int AA::TileMap::getTileWidth() const {
    return this->tileWidth;
}

unsigned int AA::TileMap::getTileHeight() const {
    return this->tileHeight;
}

unsigned int AA::TileMap::getTilesetColumns() const {
    return this->tilesetColumns;
}

unsigned int AA::TileMap::getTilesetRows() const {
    return this->tilesetRows;
}

std::string AA::TileMap::getFilename() const {
    return this->filename;
}

std::vector<int> AA::TileMap::getData() const {
    return this->data;
}

void AA::TileMap::setName(const std::string &name) {
    this->name = name;
}

void AA::TileMap::setColumns(const unsigned int columns) {
    this->columns = columns;
}

void AA::TileMap::setRows(const unsigned int rows) {
    this->rows = rows;
}

void AA::TileMap::setTileWidth(const unsigned int tileWidth) {
    this->tileWidth = tileWidth;
}

void AA::TileMap::setTileHeight(const unsigned int tileHeight) {
    this->tileHeight = tileHeight;
}

void AA::TileMap::setTilesetColumns(const unsigned int tilesetColumns) {
    this->tilesetColumns = tilesetColumns;
}

void AA::TileMap::setTilesetRows(const unsigned int tilesetRows) {
    this->tilesetRows = tilesetRows;
}

void AA::TileMap::setFilename(const std::string &filename) {
    this->filename = filename;
}

void AA::TileMap::setData(const std::vector<int> &data) {
    this->data.clear();
    this->data = data;
}

void AA::TileMap::generate() {
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(this->columns * this->rows * 4);

    sf::Vector2u tileSize = { this->tileWidth, this->tileHeight };

    for (unsigned int i = 0; i < this->columns; ++i) {
        for (unsigned int j = 0; j < this->rows; ++j) {
            int dataNr = this->data[i + j * this->columns];

            if (dataNr >= 0) {
                int index = dataNr;

                int tu = index % (this->getTexture().getSize().x / tileSize.x);
                int tv = index / (this->getTexture().getSize().x / tileSize.x);

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

void AA::TileMap::setColor(const sf::Color &color) {

}

void AA::TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &this->getTexture();
    target.draw(this->vertices, states);
}
