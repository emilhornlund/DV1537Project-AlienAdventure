/**
 * @file Hud.hpp
 * @date 2016-12-12
 * @author Emil Hörnlund
 */

#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "Core.hpp"

class Hud : public sf::Drawable, public sf::Transformable {
private:
    Game* game;

    sf::Texture* texture;

    sf::Sprite* coin;

    sf::Sprite* multiplier;

    unsigned int lifesCapacity;

    unsigned int lifesSize;

    sf::Sprite** lifes;

    unsigned int digitsCapacity;

    unsigned int digitsSize;

    sf::Sprite** digits;

    void createCoin();

    void createMultiplier();

    void clearLifes();

    void clearDigits();
public:
    Hud(Game *game);

    Hud(const Hud &original);

    ~Hud() override;

    virtual Hud& operator=(const Hud &original);

    Game* getGame() const;

    void restore();

    void setHealth(const unsigned int health);

    void setCoins(const unsigned int coins);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* Hud_hpp */
