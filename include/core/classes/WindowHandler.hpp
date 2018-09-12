/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef RENDER_HPP
#define RENDER_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Color.hpp>

class Camera;
class IGame;
class IGameObject;

namespace sf {
    class Image;
    class RenderWindow;
    class View;
    class Drawable;
}

class WindowHandler {
private:
    class RenderItem {
    private:
        unsigned int depth;

        sf::Drawable* drawable;

        bool useCamera;

        RenderItem(const RenderItem &original);

        RenderItem& operator=(const RenderItem &original);
    public:
        RenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera);

        virtual ~RenderItem();

        unsigned int getDepth() const;

        sf::Drawable* getDrawable() const;

        bool isUsingCamera() const;
    };

    IGame* m_game;

    std::vector<std::shared_ptr<RenderItem>> m_renderItems;

    std::shared_ptr<sf::RenderWindow> m_window;

    const sf::Image *m_icon;

    std::shared_ptr<Camera> m_camera;

    WindowHandler(const WindowHandler &original);

    WindowHandler& operator=(const WindowHandler &original);

    void addRenderItem(sf::Drawable *drawable, unsigned int depth, const bool useCamera);

    void sortQueue();
public:
    WindowHandler(IGame* game, const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title);

    ~WindowHandler();

    IGame* getGame() const;

    sf::RenderWindow& getRenderWindow() const;

    Camera& getCamera() const;

    void render();

    void clear(sf::Color color = sf::Color::Black);

    void draw(IGameObject &object);
};

#endif /* Renderer_hpp */
