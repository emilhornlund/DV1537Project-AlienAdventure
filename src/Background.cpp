/**
 * @file Background.hpp
 * @date 2016-12-10
 * @author Emil Hörnlund
 */


#include "Background.hpp"

const sf::Vector2i Background::SIZE = { 560, 560 };

Background::Background(Game *game) : StaticFrame(game) {
    this->columnsCapacity = 0;
    this->columnsSize = 0;
    this->columns = new unsigned int[this->columnsCapacity];

    this->rowsCapacity = 0;
    this->rowsSize = 0;
    this->rows = new unsigned int[this->rowsCapacity];
}

Background::Background(const Background &original) : StaticFrame(original) {
    this->columnsCapacity = original.columnsCapacity;
    this->columnsSize = original.columnsSize;
    this->columns = new unsigned int[this->columnsCapacity];
    for (int i = 0; i < this->columnsSize; i++) {
        this->columns[i] = original.columns[i];
    }

    this->rowsCapacity = original.rowsCapacity;
    this->rowsSize = original.rowsSize;
    this->rows = new unsigned int[this->rowsCapacity];
    for (int i = 0; i < this->rowsSize; i++) {
        this->rows[i] = original.rows[i];
    }

    this->vertices = original.vertices;
}

/**
 * Destruktorn
 */
Background::~Background() {
    delete[] this->columns;
    this->columns = nullptr;

    delete[] this->rows;
    this->rows = nullptr;
}

Background& Background::operator=(const Background &original) {
    if (this != &original) {
        delete[] this->columns;
        this->columnsCapacity = original.columnsCapacity;
        this->columnsSize = original.columnsSize;
        this->columns = new unsigned int[this->columnsCapacity];
        for (int i = 0; i < this->columnsSize; i++) {
            this->columns[i] = original.columns[i];
        }

        delete[] this->rows;
        this->rowsCapacity = original.rowsCapacity;
        this->rowsSize = original.rowsSize;
        this->rows = new unsigned int[this->rowsCapacity];
        for (int i = 0; i < this->rowsSize; i++) {
            this->rows[i] = original.rows[i];
        }

        this->vertices = original.vertices;
    }
    return *this;
}

Background* Background::clone() const {
    return new Background(*this);
}

void Background::addBackgroundSequence(const unsigned int column, const unsigned int row) {
    if (this->columnsCapacity == this->columnsSize) {
        this->columnsCapacity += 2;
        auto *tempColumns = new unsigned int[this->columnsCapacity];
        for (int i = 0; i < this->columnsSize; i++) {
            tempColumns[i] = this->columns[i];
        }
        delete[] this->columns;
        this->columns = tempColumns;
    }
    this->columns[this->columnsSize] = column;
    this->columnsSize++;

    if (this->rowsCapacity == this->rowsSize) {
        this->rowsCapacity += 2;
        auto *tempRows = new unsigned int[this->rowsCapacity];
        for (int i = 0; i < this->rowsSize; i++) {
            tempRows[i] = this->rows[i];
        }
        delete[] this->rows;
        this->rows = tempRows;
    }
    this->rows[this->rowsSize] = row;
    this->rowsSize++;
}

void Background::generate() {
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(this->columnsSize * 4);

    for (int i = 0; i < this->columnsSize; ++i) {
        unsigned int tu = this->columns[i];
        unsigned int tv = this->rows[i];

        sf::Vertex* quad = &this->vertices[i * 4];

        quad[0].position = sf::Vector2f(i * SIZE.x, 0);
        quad[1].position = sf::Vector2f((i + 1) * SIZE.x, 0);
        quad[2].position = sf::Vector2f((i + 1) * SIZE.x, SIZE.y);
        quad[3].position = sf::Vector2f(i * SIZE.x, SIZE.y);

        quad[0].texCoords = sf::Vector2f(tu * SIZE.x, tv * SIZE.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * SIZE.x, tv * SIZE.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * SIZE.x, (tv + 1) * SIZE.y);
        quad[3].texCoords = sf::Vector2f(tu * SIZE.x, (tv + 1) * SIZE.y);
    }
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = this->getTexture();
    target.draw(this->vertices, states);
}
