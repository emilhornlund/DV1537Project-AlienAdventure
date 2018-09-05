/**
 * @file Background.hpp
 * @date 2016-12-10
 * @author Emil Hörnlund
 */

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Core.hpp"
#include "StaticFrame.hpp"

class Background : public StaticFrame {
private:
    unsigned int columnsCapacity;

    unsigned int columnsSize;

    unsigned int *columns;

    unsigned int rowsCapacity;

    unsigned int rowsSize;

    unsigned int *rows;

    sf::VertexArray vertices;
public:
    static const sf::Vector2i SIZE;

    Background();

    Background(const Background &original);

    ~Background() override;

    virtual Background& operator=(const Background &original);

    Background* clone() const override;

    void addBackgroundSequence(const unsigned int column, const unsigned int row);

    void generate();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* Background_hpp */
