//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_IMENUOBJECT_HPP
#define ALIENADVENTURE_IMENUOBJECT_HPP

#include "core/interfaces/IGameObject.hpp"

#include <SFML/System/Clock.hpp>

class SpriteEntity;

namespace sf {
    class Sound;
    class Texture;
}

class IMenuObject : public IGameObject {
private:
    struct MenuItem {
        std::shared_ptr<SpriteEntity> m_entity;
        sf::IntRect unselectedTextureRect;
        sf::IntRect selectedTextureRect;
    };

    std::vector<std::shared_ptr<MenuItem>> m_menuItems;

    int m_selectedItemIndex;

    bool m_hasPendingSelection;

    sf::Clock m_selectionClock;

    std::shared_ptr<sf::Sound> m_clickSound;

    std::shared_ptr<sf::Sound> m_switchSound;

    IMenuObject(const IMenuObject &original);

    IMenuObject& operator=(const IMenuObject &original);

    void updateOffsets();
public:
    explicit IMenuObject(IGame *game);

    ~IMenuObject() override = 0;

    void addItem(const sf::IntRect& unselectedTextureRect, const sf::IntRect& selectedTextureRect, const sf::Texture& texture);

    void toggleNext();

    void togglePrevious();

    int getSelectedItemIndex() const;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override = 0;
};

#endif //ALIENADVENTURE_IMENUOBJECT_HPP
