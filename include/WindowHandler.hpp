/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef RENDER_HPP
#define RENDER_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class WindowHandler {
private:
    class RenderItem {
    private:
        unsigned int depth;

        sf::Drawable* drawable;

        bool useCamera;
    public:
        RenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera);

        RenderItem(const RenderItem &original);

        virtual RenderItem& operator=(const RenderItem &original);

        virtual ~RenderItem();

        unsigned int getDepth() const;

        sf::Drawable* getDrawable() const;

        bool isUsingCamera() const;

        bool operator>(const RenderItem& original) const;

        bool operator<(const RenderItem& original) const;

        virtual RenderItem* clone() const;
    };

    Game* game;

    unsigned int queueCapacity;

    unsigned int queueSize;

    RenderItem** queue;

    sf::RenderWindow *window;

    sf::Image *icon;

    Camera *camera;

    void clearQueue();

    void addRenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera);

    void sortQueue();
public:
    WindowHandler(Game *game, const unsigned int windowWidth, const unsigned int windowHeight,
                      const std::string &title);

    ~WindowHandler();

    Game* getGame() const;

    sf::RenderWindow* getRenderWindow();

    sf::View* getView();

    Camera& getCamera() const;

    void render();

    void clear(sf::Color color = sf::Color::Black);

    void draw(GameObject& object);
};

#endif /* Renderer_hpp */
