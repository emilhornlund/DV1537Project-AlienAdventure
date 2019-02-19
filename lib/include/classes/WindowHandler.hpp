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
#include <SFML/System/Vector2.hpp>

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
        unsigned int m_zIndex;

        std::vector<sf::Drawable*> m_drawables;

        bool m_useCamera;

        RenderItem(const RenderItem &original);

        RenderItem& operator=(const RenderItem &original);
    public:
        RenderItem(unsigned int depth, const bool useCamera);

        virtual ~RenderItem();

        unsigned int getDepth() const;

        bool isUsingCamera() const;

        void addDrawable(sf::Drawable* drawable);

        unsigned long getDrawablesSize() const;

        const sf::Drawable & getDrawable(const unsigned long index) const;
    };

    IGame* m_game;

    std::vector<std::shared_ptr<RenderItem>> m_renderItems;

    std::shared_ptr<sf::RenderWindow> m_window;

    const sf::Image *m_icon;

    std::shared_ptr<Camera> m_camera;

    WindowHandler(const WindowHandler &original);

    WindowHandler& operator=(const WindowHandler &original);

    void sortQueue();
public:
    WindowHandler(IGame* game, const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title);

    ~WindowHandler();

    IGame* getGame() const;

    sf::RenderWindow& getRenderWindow() const;

    Camera& getCamera() const;

    const sf::Vector2f& getWindowSize() const;

    void render();

    void clear(sf::Color color = sf::Color::Black);

    void draw(IGameObject &object);
};

#endif /* Renderer_hpp */
