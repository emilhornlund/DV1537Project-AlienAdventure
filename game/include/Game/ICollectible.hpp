/**
 * @file Collectible.hpp
 * @date 2016-12-09
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_COLLECTIBLE_HPP
#define ALIENADVENTURE_COLLECTIBLE_HPP

#include <Core/IGameObject.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <memory>

namespace AA { //AlienAdventure
    class ICollectible : public CGL::IGameObject {
    private:
        sf::IntRect m_spawnArea;

        bool m_collected;

        const sf::SoundBuffer *m_soundBuffer;

        std::shared_ptr<sf::Sound> m_sound;

        ICollectible(const ICollectible &original);

        ICollectible &operator=(const ICollectible &original);
    public:
        ICollectible(CGL::IGame *game, const sf::IntRect &spawnArea, const std::string &soundFilePath);

        ~ICollectible() override = 0;

        bool isCollected() const;

        void setCollected(const bool collected);

        void restore(const bool respawn) override = 0;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif /* ALIENADVENTURE_COLLECTIBLE_HPP */
