/**
 * @file Hud.cpp
 * @date 2016-12-12
 * @author Emil Hörnlund
 */

#include "Hud.hpp"

const sf::Vector2i SIZE = { 52, 48 };
const float SPACE = 10;

Hud::Hud() {
    std::string rpath = "./resources/Hud.png";
    this->texture = new sf::Texture;
    if (!this->texture->loadFromFile(rpath)) {
        throw "Failed to load " + rpath;
    }

    this->lifesCapacity = 0;
    this->lifesSize = 0;
    this->lifes = new sf::Sprite*[this->lifesCapacity];

    this->digitsCapacity = 0;
    this->digitsSize = 0;
    this->digits = new sf::Sprite*[this->digitsCapacity];

    this->createCoin();
    this->createMultiplier();
}

Hud::Hud(const Hud &original) {
    this->texture = original.texture;
    this->coin = original.coin;
    this->multiplier = original.multiplier;

    this->lifesCapacity = original.lifesCapacity;
    this->lifesSize = original.lifesSize;
    this->lifes = new sf::Sprite*[this->lifesCapacity];
    for (int i = 0; i < this->lifesSize; i++) {
        this->lifes[i] = original.lifes[i];
    }

    this->digitsCapacity = original.lifesCapacity;
    this->digitsSize = original.lifesSize;
    this->digits = new sf::Sprite*[this->digitsCapacity];
    for (int i = 0; i < this->digitsSize; i++) {
        this->digits[i] = original.digits[i];
    }
}

Hud::~Hud() {
    delete this->texture;
    delete this->coin;
    delete this->multiplier;
    this->clearLifes();
    this->clearDigits();
}

Hud& Hud::operator=(const Hud &original) {
    if (this != &original) {
        delete this->texture;
        delete this->coin;
        this->clearLifes();
        this->clearDigits();

        this->texture = original.texture;
        this->coin = original.coin;
        this->multiplier = original.multiplier;

        this->lifesCapacity = original.lifesCapacity;
        this->lifesSize = original.lifesSize;
        this->lifes = new sf::Sprite*[this->lifesCapacity];
        for (int i = 0; i < this->lifesSize; i++) {
            this->lifes[i] = original.lifes[i];
        }

        this->digitsCapacity = original.lifesCapacity;
        this->digitsSize = original.lifesSize;
        this->digits = new sf::Sprite*[this->digitsCapacity];
        for (int i = 0; i < this->digitsSize; i++) {
            this->digits[i] = original.digits[i];
        }
    }
    return *this;
}

void Hud::clearLifes() {
    for (int i = 0; i < this->lifesSize; i++) {
        delete this->lifes[i];
        this->lifes[i] = nullptr;
    }
    delete[] this->lifes;
    this->lifes = nullptr;
}

void Hud::clearDigits() {
    for (int i = 0; i < this->digitsSize; i++) {
        delete this->digits[i];
        this->digits[i] = nullptr;
    }
    delete[] this->digits;
    this->digits = nullptr;
}

void Hud::restore() {
    this->clearLifes();
    this->lifesCapacity = 0;
    this->lifesSize = 0;
    this->lifes = new sf::Sprite*[this->lifesCapacity];

    this->clearDigits();
    this->digitsCapacity = 0;
    this->digitsSize = 0;
    this->digits = new sf::Sprite*[this->digitsCapacity];
}

void Hud::createCoin() {
    this->coin = new sf::Sprite;
    this->coin->setTexture(*this->texture);

    float originX = (float)SIZE.x/2;
    float originY = (float)SIZE.y/2;
    this->coin->setOrigin({ originX, originY });

    float posX = 800 - SPACE - originX;
    float posY = SPACE + originY;
    this->coin->setPosition({ posX, posY });

    this->coin->setTextureRect({ SIZE.x*3, SIZE.y, SIZE.x, SIZE.y });
}

void Hud::createMultiplier() {
    this->multiplier = new sf::Sprite;
    this->multiplier->setTexture(*this->texture);

    float originX = (float)SIZE.x/2;
    float originY = (float)SIZE.y/2;
    this->multiplier->setOrigin({ originX, originY });

    this->multiplier->setTextureRect({ 0, SIZE.y*3, SIZE.x, SIZE.y });
}

void Hud::setHealth(const unsigned int health) {
    if (health > this->lifesSize) {
        this->clearLifes();
        this->lifesCapacity = health;
        this->lifesSize = health;
        this->lifes = new sf::Sprite*[this->lifesCapacity];
        for (int i = 0; i < health; i++) {
            this->lifes[i] = new sf::Sprite;
        }
    }
    for (int i = 0; i < this->lifesSize; i++) {
        this->lifes[i]->setTexture(*this->texture);

        float originX = (float)SIZE.x/2;
        float originY = (float)SIZE.y/2;
        this->lifes[i]->setOrigin({ originX, originY });

        float posX = (float)SIZE.x/2 + SPACE + SPACE*i + SIZE.x*i;
        float posY = (float)SIZE.y/2 + SPACE;
        this->lifes[i]->setPosition({ posX, posY });

        if (i+1 <= health) {
            this->lifes[i]->setTextureRect({ 0, SIZE.y, SIZE.x, SIZE.y });
        } else {
            this->lifes[i]->setTextureRect({ SIZE.x*2, SIZE.y, SIZE.x, SIZE.y });
        }
    }
}

void Hud::setCoins(const unsigned int coins) {
    unsigned int numberOfDigits = (int)std::to_string(coins).size();
    if (numberOfDigits > this->digitsSize) {
        this->clearDigits();
        this->digitsCapacity = numberOfDigits;
        this->digitsSize = numberOfDigits;
        this->digits = new sf::Sprite*[this->digitsCapacity];
        for (int i = 0; i < numberOfDigits; i++) {
            this->digits[i] = new sf::Sprite;
        }
    }
    auto minX = (float)(800 - SIZE.x - ((SIZE.x-15)*numberOfDigits));
    this->multiplier->setPosition({ (minX - (SIZE.x-15)), ((SIZE.y/2 + SPACE) + 4) });
    for (int i = 0; i < this->digitsSize; i++) {
        this->digits[i]->setTexture(*this->texture);

        float originX = (float)SIZE.x/2;
        float originY = (float)SIZE.y/2;
        this->digits[i]->setOrigin({ originX, originY });

        float posX = minX + (SIZE.x-15)*i;
        float posY = (float)SIZE.y/2 + SPACE;
        this->digits[i]->setPosition({ posX, posY });

        int digit = std::to_string(coins)[i] - '0';
        this->digits[i]->setTextureRect({ SIZE.x*(digit+1), SIZE.y*3, SIZE.x, SIZE.y });
    }
}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < this->lifesSize; i++) {
        target.draw(*this->lifes[i]);
    }
    for (int i = 0; i < this->digitsSize; i++) {
        target.draw(*this->digits[i]);
    }
    target.draw(*this->coin);
    target.draw(*this->multiplier, states);
}
