//
// Created by Emil Hörnlund on 2018-09-07.
//

#ifndef ALIENADVENTURE_IENTITY_HPP
#define ALIENADVENTURE_IENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sf {
    class Color;
}

class IEntity : public sf::Drawable, public sf::Transformable {
private:
    const sf::Texture* m_texture;

    sf::Vector2f m_offset;

    IEntity(const IEntity &original);

    IEntity& operator=(const IEntity &original);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
public:
    IEntity();

    ~IEntity() override = 0;

    void setTexture(const sf::Texture& texture);

    const sf::Texture& getTexture() const;

    void setOffset(const sf::Vector2f& offset);

    void setOffset(const float x, const float y);

    const sf::Vector2f& getOffset() const;

    virtual void setColor(const sf::Color& color) = 0;
};

#endif //ALIENADVENTURE_IENTITY_HPP
