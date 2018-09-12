/**
 * @file GameObject.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <memory>
#include <vector>

class IGame;
class IEntity;

class IGameObject {
public:
    static const int DRAW_ORDER_HUD = 0;
    static const int DRAW_ORDER_ENEMY_DEAD = 1;
    static const int DRAW_ORDER_PLAYER = 2;
    static const int DRAW_ORDER_ENEMY_ALIVE = 3;
    static const int DRAW_ORDER_COLLECTIBLE = 4;
    static const int DRAW_ORDER_TILEMAP = 5;
    static const int DRAW_ORDER_BACKGROUND = 6;
private:
    IGame* m_game;

    std::vector<std::shared_ptr<IEntity>> m_entities;

    int m_zIndex;

    bool m_useCamera;

    bool m_visible;

    sf::Vector2f m_position;

    sf::Vector2f m_velocity;

    sf::Vector2f m_acceleration;

    sf::IntRect m_boundingBox;

    IGameObject(const IGameObject &original);

    IGameObject& operator=(const IGameObject &original);
public:
    IGameObject(IGame *game, const int zIndex, const bool useCamera);

    virtual ~IGameObject();

    IGame* getGame() const;

    void addEntity(IEntity* entity);

    unsigned long getEntitiesSize() const;

    IEntity& getEntity(unsigned long index) const;

    void clearEntities();

    virtual void restore(const bool respawn) = 0;

    virtual void processEvents() = 0;

    virtual void update(const float dt) = 0;

    int getZIndex() const;

    void setZIndex(const int depth);

    bool isVisible() const;

    void setVisible(const bool visible);

    bool isUsingCamera() const;

    void setPosition(const sf::Vector2f& position);

    void move(const sf::Vector2f& moveBy);

    sf::Vector2f getPosition() const;

    void setVelocity(const sf::Vector2f& velocity);

    sf::Vector2f getVelocity() const;

    void setAcceleration(const sf::Vector2f& acceleration);

    sf::Vector2f getAcceleration() const;

    void updateSprites();

    sf::IntRect getBoundingBox() const;

    void setBoundingBox(const sf::IntRect& boundingBox);
};

#endif /* GameObject_h */
