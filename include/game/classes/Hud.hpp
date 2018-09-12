//
// Created by Emil Hörnlund on 2018-09-08.
//

#ifndef ALIENADVENTURE_HUD_HPP
#define ALIENADVENTURE_HUD_HPP

#include "core/interfaces/IGameObject.hpp"

#include <vector>

class IGame;
class SpriteEntity;

class Hud : public IGameObject {
private:
    unsigned int m_currentHealth;

    unsigned int m_currentCoins;

    std::vector<SpriteEntity*> m_healthSprites;

    std::vector<SpriteEntity*> m_coinDigitSprites;

    SpriteEntity* m_coinSprite;

    SpriteEntity* m_coinMultiplierSprite;

    Hud(const Hud &original);

    Hud& operator=(const Hud &original);

    void updateHealth(const unsigned health);

    void updateCoins(const unsigned coins);

    void setupCoin();

    void setupCoinInitialDigit();

    void setupCoinMultiplier();
public:
    explicit Hud(IGame* game);

    ~Hud() override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif //ALIENADVENTURE_HUD_HPP
