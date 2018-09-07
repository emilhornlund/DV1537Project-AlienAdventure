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
    Game* game;

    sf::Texture* texture;

    sf::Vector2f offset;

    StaticFrame(const StaticFrame &original);

    StaticFrame& operator=(const StaticFrame &original);
public:
    explicit StaticFrame(Game *game);

    ~StaticFrame() override;

    Game* getGame() const;

    void setTexture(sf::Texture* texture);

    bool loadTextureFromFile(const std::string &filename);

    sf::Texture* getTexture() const;

    sf::Vector2f getOffset() const;

    void setOffset(const sf::Vector2f offset);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

#endif /* StaticFrame_hpp */
