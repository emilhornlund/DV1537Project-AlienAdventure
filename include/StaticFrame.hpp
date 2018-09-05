/**
 * @file StaticFrame.hpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#ifndef STATIC_FRAME_H
#define STATIC_FRAME_H

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class StaticFrame : public sf::Drawable, public sf::Transformable {
private:
    sf::Texture* texture;

    sf::Vector2f offset;
public:
    StaticFrame();

    StaticFrame(const StaticFrame &original);

    ~StaticFrame() override;

    virtual StaticFrame& operator=(const StaticFrame &original);

    virtual StaticFrame* clone() const = 0;

    void setTexture(sf::Texture* texture);

    bool loadTextureFromFile(const std::string &filename);

    sf::Texture* getTexture() const;

    sf::Vector2f getOffset() const;

    void setOffset(const sf::Vector2f offset);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

#endif /* StaticFrame_hpp */
