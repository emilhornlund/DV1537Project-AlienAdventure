/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include <Core/Camera.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/WindowHandler.hpp>
#include <Core/IEntity.hpp>
#include <Core/IGame.hpp>
#include <Core/IGameObject.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

CGL::WindowHandler::WindowHandler(CGL::IGame* game, const unsigned int windowWidth, const unsigned int windowHeight, const std::string &title) : m_game(game) {
    this->m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight, 32), title, sf::Style::Titlebar | sf::Style::Close);
    this->m_window->setKeyRepeatEnabled(true);
    this->m_window->setMouseCursorVisible(false);
    this->m_window->setVerticalSyncEnabled(true);

    this->m_icon = &this->getGame()->getImageResourceHandler().load("Icon.png");
    this->m_window->setIcon(this->m_icon->getSize().x, this->m_icon->getSize().y, this->m_icon->getPixelsPtr());

    this->m_camera = std::make_shared<Camera>(sf::FloatRect(0, 0, windowWidth, windowHeight));
    this->m_window->setView(this->m_camera->getView());
}

CGL::WindowHandler::~WindowHandler() = default;

CGL::IGame* CGL::WindowHandler::getGame() const {
    return this->m_game;
}

void CGL::WindowHandler::sortQueue() {
    std::sort(this->m_renderItems.begin(), this->m_renderItems.end(), [](const std::shared_ptr<RenderItem> &lhs, const std::shared_ptr<RenderItem> &rhs) -> bool {
        return lhs->getDepth() > rhs->getDepth();
    });
};

sf::RenderWindow& CGL::WindowHandler::getRenderWindow() const {
    return *this->m_window;
}

CGL::Camera& CGL::WindowHandler::getCamera() const {
    return *this->m_camera;
}

const sf::Vector2f &CGL::WindowHandler::getWindowSize() const {
    return this->getCamera().getView().getSize();
}

void CGL::WindowHandler::render() {
    this->sortQueue();
    for (const auto& item : this->m_renderItems) {
        if (item->isUsingCamera()) {
            this->m_window->setView(this->m_camera->getView());
        } else {
            this->m_window->setView(this->m_window->getDefaultView());
        }
        for (unsigned long i = 0; i < item->getDrawablesSize(); i++) {
            this->m_window->draw(item->getDrawable(i));
        }
    }
    this->m_window->setView(this->m_window->getDefaultView());
    this->m_window->display();
    this->m_renderItems.clear();
}

void CGL::WindowHandler::clear(sf::Color color) {
    this->m_window->clear(color);
}

void CGL::WindowHandler::draw(IGameObject &object) {
    std::vector<sf::Drawable*> drawables;
    if (object.getEntitiesSize() > 0 && object.isVisible()) {
        std::shared_ptr<RenderItem> item = std::make_shared<RenderItem>(object.getZIndex(), object.isUsingCamera());
        for (unsigned long i = 0; i < object.getEntitiesSize(); i++) {
            item->addDrawable(&object.getEntity(i));
        }
        this->m_renderItems.push_back(item);
        object.updateSprites();
    }
}

CGL::WindowHandler::RenderItem::RenderItem(unsigned int depth, const bool useCamera) : m_zIndex(depth), m_useCamera(useCamera) {}

CGL::WindowHandler::RenderItem::~RenderItem() = default;

unsigned int CGL::WindowHandler::RenderItem::getDepth() const {
    return this->m_zIndex;
}

bool CGL::WindowHandler::RenderItem::isUsingCamera() const {
    return this->m_useCamera;
}

void CGL::WindowHandler::RenderItem::addDrawable(sf::Drawable *drawable) {
    this->m_drawables.push_back(drawable);
}

unsigned long CGL::WindowHandler::RenderItem::getDrawablesSize() const {
    return this->m_drawables.size();
}

const sf::Drawable& CGL::WindowHandler::RenderItem::getDrawable(const unsigned long index) const {
    return *this->m_drawables.at(index);
}
