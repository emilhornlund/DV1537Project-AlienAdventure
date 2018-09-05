/**
 * @file Menu.hpp
 * @date 2016-12-12
 * @author Emil Hörnlund
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Core.hpp"

enum class MenuType { Pause, Respawn, GameOver };

class Menu : public sf::Drawable, public sf::Transformable {
private:
    MenuType type;

    sf::Texture* texture;

    sf::SoundBuffer* switchBuffer;

    sf::Sound* switchSound;

    unsigned int buttonsCapacity;

    unsigned int buttonsSize;

    sf::Sprite** buttons;

    unsigned int currentButton;

    void updateSelection();
public:
    explicit Menu(MenuType type);

    Menu(const Menu &original);

    ~Menu() override;

    Menu& operator=(const Menu &original);

    sf::Vector2i getSize() const;

    void toggleNext();

    void togglePrevious();

    unsigned int getSelection() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* Menu_hpp */
