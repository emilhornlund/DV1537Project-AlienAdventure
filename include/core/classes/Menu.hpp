/**
 * @file Menu.hpp
 * @date 2016-12-12
 * @author Emil Hörnlund
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

class IGame;

namespace sf {
    class SoundBuffer;
    class Sound;
    class Sprite;
}

class Menu : public sf::Drawable, public sf::Transformable {
public:
    enum class MenuType { Pause, Respawn, GameOver };
private:
    IGame* game;

    MenuType type;

    const sf::Texture* texture;

    const sf::SoundBuffer* switchBuffer;

    std::shared_ptr<sf::Sound> switchSound;

    unsigned int buttonsCapacity;

    unsigned int buttonsSize;

    sf::Sprite** buttons;

    unsigned int currentButton;

    Menu(const Menu &original);

    Menu& operator=(const Menu &original);

    void updateSelection();
public:
    Menu(IGame* game, MenuType type);

    ~Menu() override;

    IGame* getGame() const;

    sf::Vector2i getSize() const;

    void toggleNext();

    void togglePrevious();

    unsigned int getSelection() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* Menu_hpp */
