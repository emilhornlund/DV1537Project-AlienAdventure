//
// Created by Emil Hörnlund on 2018-09-07.
//

#ifndef ALIENADVENTURE_SPRITEENTITY_HPP
#define ALIENADVENTURE_SPRITEENTITY_HPP

#include "core/interfaces/IEntity.hpp"

#include <SFML/Graphics/Vertex.hpp>

#include <memory>

class SpriteEntity : public IEntity {
private:
    sf::Vertex m_vertices[4];

    SpriteEntity(const SpriteEntity &original);

    SpriteEntity& operator=(const SpriteEntity &original);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    SpriteEntity();

    ~SpriteEntity() override;

    void setTextureRect(const sf::IntRect& rectangle);

    void setColor(const sf::Color& color) override;
};

#endif //ALIENADVENTURE_SPRITEENTITY_HPP
