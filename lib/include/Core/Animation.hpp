//
// Created by Emil Hörnlund on 2018-09-08.
//

#ifndef COREGAMELIB_ANIMATION_HPP
#define COREGAMELIB_ANIMATION_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

namespace sf { //SFML
    class Texture;
}

namespace CGL { //CoreGameLib
    class Animation {
    private:
        sf::Time m_frameTime;

        bool m_isLooped;

        std::vector<sf::IntRect> m_frames;

        const sf::Texture *m_texture;

        Animation(const Animation &original);

        Animation &operator=(const Animation &original);
    public:
        explicit Animation(sf::Time frameTime = sf::seconds(0.2f), bool looped = true);

        ~Animation();

        void addFrame(const sf::IntRect &rect);

        void setSpriteSheet(const sf::Texture &texture);

        const sf::Texture *getSpriteSheet() const;

        unsigned long getSize() const;

        const sf::IntRect &getFrame(unsigned long index) const;

        void setFrameTime(sf::Time time);

        sf::Time getFrameTime() const;

        void setLooped(bool looped);

        bool isLooped() const;
    };
}

#endif //COREGAMELIB_ANIMATION_HPP
