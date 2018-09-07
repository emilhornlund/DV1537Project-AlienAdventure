/**
 * @file StaticFrame.cpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#include "StaticFrame.hpp"
#include "Game.hpp"
#include "ResourceHandler.hpp"

StaticFrame::StaticFrame(Game *game) {
    this->game = game;
    this->texture = nullptr;
}

StaticFrame::~StaticFrame() = default;

Game* StaticFrame::getGame() const {
    return this->game;
}

void StaticFrame::setTexture(sf::Texture* texture) {
    this->texture = new sf::Texture(*texture); //TODO: kolla denna
}

bool StaticFrame::loadTextureFromFile(const std::string &filename) {
    if (!this->getGame()->getTextureResourceHandler()->isLoaded(filename))
        this->getGame()->getTextureResourceHandler()->load(filename);
    this->texture = &this->getGame()->getTextureResourceHandler()->get(filename);
    return true; //TODO: kolla detta
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
