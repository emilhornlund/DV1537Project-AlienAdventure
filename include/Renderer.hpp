/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef RENDER_HPP
#define RENDER_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class RenderItem {
private:
    unsigned int depth;

    sf::Drawable* drawable;
public:
    RenderItem(sf::Drawable* drawable, unsigned int depth);

    RenderItem(const RenderItem &original);

    virtual RenderItem& operator=(const RenderItem &original);

    virtual ~RenderItem();

    unsigned int getDepth() const;

    sf::Drawable* getDrawable() const;

    bool operator>(const RenderItem& original) const;

    bool operator<(const RenderItem& original) const;

    virtual RenderItem* clone() const;
};

class Renderer {
private:
    Game* game;

    unsigned int queueCapacity;

    unsigned int queueSize;

    RenderItem** queue;

    sf::RenderWindow *window;

    sf::View *view;

    void clearQueue();

    void addRenderItem(sf::Drawable* drawable, unsigned int depth);

    void sortQueue();
public:
    Renderer(Game *game, const sf::Vector2u windowSize, const std::string &title);

    ~Renderer();

    sf::RenderWindow* getRenderWindow();

    sf::View* getView();

    void updateCamera(const sf::Vector2f position);

    void render();

    void fitViewToWindow();

    void clear(sf::Color color = sf::Color::Black);

    void draw(GameObject& object);
};

#endif /* Renderer_hpp */
