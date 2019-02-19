//
// Created by Emil Hörnlund on 2018-09-08.
//

#ifndef ALIENADVENTURE_HUD_HPP
#define ALIENADVENTURE_HUD_HPP

#include <Core/IGameObject.hpp>

#include <vector>
#include <memory>

namespace CGL { //CoreGameLib
    class IGame;
    class SpriteEntity;
}

namespace AA { //AlienAdventure
    class Hud : public CGL::IGameObject {
    private:
        unsigned int m_currentHealth;

        unsigned int m_currentCoins;

        std::vector<std::shared_ptr<CGL::SpriteEntity>> m_healthSprites;

        std::vector<std::shared_ptr<CGL::SpriteEntity>> m_coinDigitSprites;

        std::shared_ptr<CGL::SpriteEntity> m_coinSprite;

        std::shared_ptr<CGL::SpriteEntity> m_coinMultiplierSprite;

        Hud(const Hud &original);

        Hud &operator=(const Hud &original);

        void updateHealth(const unsigned health);

        void updateCoins(const unsigned coins);

        void setupCoin();

        void setupCoinInitialDigit();

        void setupCoinMultiplier();
    public:
        explicit Hud(CGL::IGame *game);

        ~Hud() override;

        void restore(const bool respawn) override;

        void processEvents() override;

        void update(const float dt) override;
    };
}

#endif //ALIENADVENTURE_HUD_HPP
