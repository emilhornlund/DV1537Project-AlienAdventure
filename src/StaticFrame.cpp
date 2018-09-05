/**
 * @file StaticFrame.cpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#include "StaticFrame.hpp"

StaticFrame::StaticFrame() {
    this->texture = new sf::Texture;
}

StaticFrame::StaticFrame(const StaticFrame &original) {
    this->setTexture(original.texture);
    this->offset = original.getOffset();
}

StaticFrame::~StaticFrame() {
    delete this->texture;
    this->texture = nullptr;
}

StaticFrame& StaticFrame::operator=(const StaticFrame &original) {
    if (this != &original) {
        delete this->texture;
        this->texture = new sf::Texture(*original.texture);
        this->offset = original.getOffset();
    }
    return *this;
}

void StaticFrame::setTexture(sf::Texture* texture) {
    this->texture = new sf::Texture(*texture);
}

bool StaticFrame::loadTextureFromFile(const std::string &filename) {
    bool success = true;
    if (!this->texture->loadFromFile(filename)) {
        success = false;
    }
    return success;
}

sf::Texture* StaticFrame::getTexture() const {
    return this->texture;
}

void StaticFrame::setOffset(const sf::Vector2f offset) {
    this->offset = offset;
}

sf::Vector2f StaticFrame::getOffset() const {
    return this->offset;
}
