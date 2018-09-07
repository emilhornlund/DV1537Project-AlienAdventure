//
// Created by Emil Hörnlund on 2018-09-07.
//

#ifndef ALIENADVENTURE_COLLECTIBLEBAROBJECT_HPP
#define ALIENADVENTURE_COLLECTIBLEBAROBJECT_HPP

#include "Core.hpp"
#include "GameObject.hpp"
#include "StaticFrame.hpp"

class CollectibleBarObject : public GameObject {
private:
    class SpriteStaticFrame : public StaticFrame {
    private:
        sf::Sprite *sprite;
    public:
        explicit SpriteStaticFrame(Game *game);

        SpriteStaticFrame(const SpriteStaticFrame &original);

        ~SpriteStaticFrame() override;

        SpriteStaticFrame& operator=(const SpriteStaticFrame &original);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Sprite& getSprite() const;

        void loadSpriteTextureFromFile(const std::string filePath);
    };

    unsigned int currentCoins;

    CollectibleBarObject(const CollectibleBarObject &original);

    CollectibleBarObject& operator=(const CollectibleBarObject &original);

    void createCoin();

    void createMultiplier();

    void createFirstDigitCoin();
public:
    explicit CollectibleBarObject(Game *game);

    ~CollectibleBarObject() override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};


#endif //ALIENADVENTURE_COLLECTIBLEBAROBJECT_HPP
