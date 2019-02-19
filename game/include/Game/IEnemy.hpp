/**
 * @file Enemy.hpp
 * @date 2016-11-28
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_ENEMY_HPP
#define ALIENADVENTURE_ENEMY_HPP

#include <Core/IGameObject.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace CGL { //CoreGameLib
    class Animation;
}

namespace AA { //AlienAdventure
    class IEnemy : public CGL::IGameObject {
    public:
        enum class EnemyDirection {
            None, Left, Right
        };
    private:
        EnemyDirection m_direction;

        sf::IntRect m_spawnArea;

        bool m_alive;

        sf::SoundBuffer *m_soundBuffer;

        sf::Sound *m_sound;

        IEnemy(const IEnemy &original);

        IEnemy &operator=(const IEnemy &original);

        void handleMovement(const float dt);

        void handleAnimation(const float dt);

        virtual const CGL::Animation &getMovingAnimation() const = 0;

        virtual const CGL::Animation &getDeadAnimation() const = 0;
    public:
        IEnemy(CGL::IGame *game, const sf::IntRect &spawnArea);

        ~IEnemy() override = 0;

        const EnemyDirection &getDirection() const;

        bool isAlive();

        void setDead();

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif /* ALIENADVENTURE_ENEMY_HPP */
