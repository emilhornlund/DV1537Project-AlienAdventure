/**
 * @file Background.hpp
 * @date 2016-12-10
 * @author Emil Hörnlund
 */

#include <Core/Camera.hpp>
#include <Core/PropertyHandler.hpp>
#include <Core/ResourceHandler.hpp>
#include <Core/SpriteEntity.hpp>
#include <Core/WindowHandler.hpp>

#include <Game/Game.hpp>
#include <Game/GameScene.hpp>
#include <Game/ParallaxBackground.hpp>

#include <SFML/Graphics/Texture.hpp>

#include <cmath>

const std::string LAYER1_TEXTURE_FILEPATH = "Hill.png";
const float LAYER1_TEXTURE_WIDTH = 640.f;
const float LAYER1_TEXTURE_HEIGHT = 256.f;
const float LAYER1_SPEED = 50.f;

const std::string LAYER2_TEXTURE_FILEPATH = "CloudsBg1.png";
const float LAYER2_TEXTURE_WIDTH = 640.f;
const float LAYER2_TEXTURE_HEIGHT = 350.f;
const float LAYER2_SPEED = LAYER1_SPEED*0.6f;

const std::string LAYER3_TEXTURE_FILEPATH = "CloudsBg2.png";
const float LAYER3_TEXTURE_WIDTH = 640.f;
const float LAYER3_TEXTURE_HEIGHT = 420.f;
const float LAYER3_SPEED = LAYER1_SPEED*0.5f;

AA::ParallaxBackground::ParallaxBackground(CGL::IGame *game) : IGameObject(game, GameScene::DRAW_ORDER_BACKGROUND, false) {
    this->setupLayer(3);
    this->setupLayer(2);
    this->setupLayer(1);
    this->m_lastCenter = this->getGame()->getWindowHandler().getCamera().getCenter();
}

AA::ParallaxBackground::~ParallaxBackground() = default;

void AA::ParallaxBackground::restore(const bool respawn) {

}

void AA::ParallaxBackground::processEvents() {

}

void AA::ParallaxBackground::update(const float dt) {
    const auto &newCenter = this->getGame()->getWindowHandler().getCamera().getCenter();
    if (newCenter == this->m_lastCenter) {
        return;
    }

    if (this->m_lastCenter != newCenter) {
        const auto windowSize = this->getGame()->getWindowHandler().getWindowSize();
        const auto worldSize = this->getGame()->getPropertyHandler().get<sf::Vector2i>("worldSize");

        auto dv = this->m_lastCenter - newCenter;

        for (unsigned long i = 0; i < this->m_layers.size(); i++) {
            float speed;
            float factor;
            switch (i) {
                case 0: //layer 3
                    speed = LAYER3_SPEED;
                    factor = 0.5f;
                    break;
                case 1: //layer 2
                    speed = LAYER2_SPEED;
                    factor = 0.75f;
                    break;
                case 2: //layer 1
                    speed = LAYER1_SPEED;
                    factor = 1.0f;
                    break;
                default:
                    speed = 0;
                    factor = 0;
                    break;
            }
            for (auto& object : this->m_layers.at(i)) {
                auto offset = object->getOffset();
                offset.x += dv.x * dt * speed;
                offset.y = (windowSize.y - object->getOrigin().y) + (object->getOrigin().y*3) * (1.f - (newCenter.y/(worldSize.y-(windowSize.y/2)))) * factor;
                object->setOffset(offset);
            }
            if (this->m_lastCenter.x != newCenter.x) {
                if (newCenter.x > this->m_lastCenter.x) {
                    auto front = this->m_layers.at(i).front();
                    if ((front->getOffset().x + front->getOrigin().x) < 0) {
                        auto back = this->m_layers.at(i).back();
                        auto offset = front->getOffset();
                        offset.x = back->getOffset().x + (front->getOrigin().x*2);
                        front->setOffset(offset);
                        std::rotate(this->m_layers.at(i).begin(), this->m_layers.at(i).begin() + 1, this->m_layers.at(i).end());
                    }
                } else {
                    auto back = this->m_layers.at(i).back();
                    if ((back->getOffset().x - back->getOrigin().x) > windowSize.x) {
                        auto front = this->m_layers.at(i).front();
                        auto offset = back->getOffset();
                        offset.x = front->getOffset().x - (back->getOrigin().x*2);
                        back->setOffset(offset);
                        std::rotate(this->m_layers.at(i).begin(), this->m_layers.at(i).begin() + this->m_layers.at(i).size() - 1, this->m_layers.at(i).end());
                    }
                }
            }
        }
    }
    this->m_lastCenter = newCenter;
}

void AA::ParallaxBackground::setupLayer(const unsigned int layer) {
    std::string textureFilePath;
    float textureWidth;
    float textureHeight;
    switch (layer) {
        case 1:
            textureFilePath = LAYER1_TEXTURE_FILEPATH;
            textureWidth = LAYER1_TEXTURE_WIDTH;
            textureHeight = LAYER1_TEXTURE_HEIGHT;
            break;
        case 2:
            textureFilePath = LAYER2_TEXTURE_FILEPATH;
            textureWidth = LAYER2_TEXTURE_WIDTH;
            textureHeight = LAYER2_TEXTURE_HEIGHT;
            break;
        case 3:
            textureFilePath = LAYER3_TEXTURE_FILEPATH;
            textureWidth = LAYER3_TEXTURE_WIDTH;
            textureHeight = LAYER3_TEXTURE_HEIGHT;
            break;
        default:
            return;
    }

    const auto& windowSize = this->getGame()->getWindowHandler().getWindowSize();
    const auto n = (unsigned int)(ceil(windowSize.x / textureWidth) + 1);
    const auto& hillTexture = this->getGame()->getTextureResourceHandler().load(textureFilePath);
    const auto startX = textureWidth - (textureWidth*n)/2;
    std::vector<std::shared_ptr<CGL::SpriteEntity>> v;
    for (unsigned int i = 0; i < n; i++) {
        auto entity = std::make_shared<CGL::SpriteEntity>();
        entity->setTexture(hillTexture);
        entity->setTextureRect({0, 0, (int)textureWidth, (int)textureHeight});
        entity->setOrigin(textureWidth/2, textureHeight/2);
        entity->setOffset(startX + (textureWidth*i), windowSize.y - textureHeight/2);
        this->addEntity(entity);
        v.push_back(entity);
    }
    this->m_layers.push_back(v);
}
