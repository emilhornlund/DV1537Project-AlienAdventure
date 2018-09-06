//
// Created by Emil Hörnlund on 2018-09-06.
//

#ifndef ALIENADVENTURE_HEALTHBAROBJECT_HPP
#define ALIENADVENTURE_HEALTHBAROBJECT_HPP

#include "GameObject.hpp"
#include "StaticFrame.hpp"

class HealthBarObject : public GameObject {
private:
    class HealthBarObjectStaticFrame : public StaticFrame {
    private:
        sf::Sprite *sprite;
    public:
        explicit HealthBarObjectStaticFrame(Game *game);

        HealthBarObjectStaticFrame(const HealthBarObjectStaticFrame &original);

        ~HealthBarObjectStaticFrame() override;

        HealthBarObjectStaticFrame& operator=(const HealthBarObjectStaticFrame &original);

        HealthBarObjectStaticFrame* clone() const override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Sprite& getSprite() const;
    };

    unsigned int currentHealth;
public:
    explicit HealthBarObject(Game *game);

    HealthBarObject(const HealthBarObject &original);

    HealthBarObject& operator=(const HealthBarObject &original);

    ~HealthBarObject() override;

    virtual GameObject* clone() const override;

    void restore(const bool respawn) override;

    void processEvents() override;

    void update(const float dt) override;
};

#endif //ALIENADVENTURE_HEALTHBAROBJECT_HPP