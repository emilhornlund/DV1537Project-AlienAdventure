/**
 * @file GameObject.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef COREGAMELIB_GAMEOBJECT_HPP
#define COREGAMELIB_GAMEOBJECT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <memory>
#include <vector>

namespace CGL { //CoreGameLib
    class IGame;
    class IEntity;

    class IGameObject {
    private:
        IGame *m_game;

        std::vector<std::shared_ptr<IEntity>> m_entities;

        int m_zIndex;

        bool m_useCamera;

        bool m_visible;

        sf::Vector2f m_position;

        sf::Vector2f m_velocity;

        sf::Vector2f m_acceleration;

        sf::IntRect m_boundingBox;

        IGameObject(const IGameObject &original);

        IGameObject &operator=(const IGameObject &original);
    public:
        IGameObject(IGame *game, const int zIndex, const bool useCamera);

        virtual ~IGameObject();

        IGame *getGame() const;

        void addEntity(std::shared_ptr<IEntity> entity);

        unsigned long getEntitiesSize() const;

        IEntity &getEntity(unsigned long index) const;

        void clearEntities();

        virtual void restore(const bool respawn) = 0;

        virtual void processEvents() = 0;

        virtual void update(const float dt) = 0;

        int getZIndex() const;

        void setZIndex(const int depth);

        bool isVisible() const;

        void setVisible(const bool visible);

        bool isUsingCamera() const;

        void setPosition(const sf::Vector2f &position);

        void move(const sf::Vector2f &moveBy);

        sf::Vector2f getPosition() const;

        void setVelocity(const sf::Vector2f &velocity);

        sf::Vector2f getVelocity() const;

        void setAcceleration(const sf::Vector2f &acceleration);

        sf::Vector2f getAcceleration() const;

        void updateSprites();

        sf::IntRect getBoundingBox() const;

        void setBoundingBox(const sf::IntRect &boundingBox);
    };
}

#endif /* COREGAMELIB_GAMEOBJECT_HPP */
