/**
 * @file GameObject.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class GameObject {
private:
    Game* game;

    AnimationHandler *animation;

    int depth;

    bool useCamera;

    bool visible;

    sf::Vector2f position;

    sf::Vector2f velocity;

    sf::Vector2f acceleration;

    sf::IntRect boundingBox;

    GameObject(const GameObject &original);

    GameObject& operator=(const GameObject &original);
public:
    static const int PLAYER_DEPTH = 1;

    static const int ENEMY_ALIVE_DEPTH = 3;

    static const int ENEMY_DEAD_DEPTH = 0;

    static const int COLLECTIBLE_DEPTH = 2;

    static const int TILELAYER_DEPTH = 4;

    static const int BACKGROUND_DEPTH = 5;

    explicit GameObject(Game *game, const bool useCamera);

    virtual ~GameObject();

    Game* getGame() const;

    virtual void restore(const bool respawn = false) = 0;

    virtual void processEvents() = 0;

    virtual void update(const float dt) = 0;

    int getDepth() const;

    void setDepth(const int depth);

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

    AnimationHandler* getAnimationHandler() const;

    void updateSprites();

    sf::IntRect getBoundingBox() const;

    void setBoundingBox(const sf::IntRect boundingBox);
};

#endif /* GameObject_h */
