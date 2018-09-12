/**
 * @file Background.hpp
 * @date 2016-12-10
 * @author Emil Hörnlund
 */

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "core/interfaces/IEntity.hpp"

#include <SFML/Graphics/VertexArray.hpp>

class IGame;

class Background : public IEntity {
private:
    unsigned int columnsCapacity;

    unsigned int columnsSize;

    unsigned int *columns;

    unsigned int rowsCapacity;

    unsigned int rowsSize;

    unsigned int *rows;

    sf::VertexArray vertices;

    Background(const Background &original);

    Background& operator=(const Background &original);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    static const sf::Vector2i SIZE;

    explicit Background();

    ~Background() override;

    void addBackgroundSequence(const unsigned int column, const unsigned int row);

    void generate();

    void setColor(const sf::Color& color) override;
};

#endif /* Background_hpp */
