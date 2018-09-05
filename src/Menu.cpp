/**
 * @file Menu.cpp
 * @date 2016-12-12
 * @author Emil Hörnlund
 */

#include "Menu.hpp"

const sf::Vector2i BUTTON_SIZE = { 480, 64 };
const float SPACE = 20;

Menu::Menu(MenuType type) {
    std::string rpath = "./resources/Menu.png";
    this->texture = new sf::Texture;
    if (!this->texture->loadFromFile(rpath)) {
        throw "Failed to load " + rpath;
    }

    rpath = "./resources/Switch.wav";
    this->switchBuffer = new sf::SoundBuffer;
    if (!this->switchBuffer->loadFromFile(rpath)) {
        throw "Failed to load " + rpath;
    }
    this->switchSound = new sf::Sound;
    this->switchSound->setBuffer(*this->switchBuffer);
    this->switchSound->setVolume(100);

    this->type = type;

    switch (type) {
        case MenuType::Pause: {
            this->buttonsCapacity = 3;
            this->buttonsSize = this->buttonsCapacity;
            this->currentButton = 0;
        } break;
        case MenuType::Respawn: {
            this->buttonsCapacity = 3;
            this->buttonsSize = this->buttonsCapacity;
            this->currentButton = 0;
        } break;
        case MenuType::GameOver: {
            this->buttonsCapacity = 3;
            this->buttonsSize = 2;
            this->currentButton = 0;
        } break;
    }

    this->buttons = new sf::Sprite*[this->buttonsCapacity];
    for (int i = 0; i < this->buttonsSize; i++) {
        this->buttons[i] = new sf::Sprite;
        float posY = BUTTON_SIZE.y*i + SPACE*i;
        this->buttons[i]->setPosition({0, posY});
    }

    this->updateSelection();
}

Menu::Menu(const Menu &original) {
    this->type = original.type;
    this->texture = original.texture;
    this->switchBuffer = original.switchBuffer;
    this->switchSound = original.switchSound;

    this->buttonsCapacity = original.buttonsCapacity;
    this->buttonsSize = original.buttonsSize;

    this->buttons = new sf::Sprite*[this->buttonsCapacity];
    for (int i = 0; i < this->buttonsSize; i++) {
        this->buttons[i] = original.buttons[i];
    }

    this->currentButton = original.currentButton;
}

Menu::~Menu() {
    delete this->texture;
    this->texture = nullptr;

    delete this->switchBuffer;
    this->switchBuffer = nullptr;

    delete this->switchSound;
    this->switchSound = nullptr;

    for (int i = 0; i < this->buttonsSize; i++) {
        delete this->buttons[i];
        this->buttons[i] = nullptr;
    }
    delete[] this->buttons;
    this->buttons = nullptr;
}

Menu& Menu::operator=(const Menu &original) {
    if (this != &original) {
        this->type = original.type;

        delete this->texture;
        this->texture = original.texture;

        delete this->switchBuffer;
        this->switchBuffer = original.switchBuffer;

        delete this->switchSound;
        this->switchSound = original.switchSound;

        for (int i = 0; i < this->buttonsSize; i++) {
            delete this->buttons[i];
            this->buttons[i] = nullptr;
        }
        delete[] this->buttons;
        this->buttons = nullptr;

        this->buttonsCapacity = original.buttonsCapacity;
        this->buttonsSize = original.buttonsSize;

        this->buttons = new sf::Sprite*[this->buttonsCapacity];
        for (int i = 0; i < this->buttonsSize; i++) {
            this->buttons[i] = original.buttons[i];
        }

        this->currentButton = original.currentButton;
    }
    return *this;
}

void Menu::updateSelection() {
    for (int i = 0; i < this->buttonsSize; i++) {
        int texturePosY = 0;
        switch (this->type) {
            case MenuType::Pause:
                if (i == 0) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*2 : BUTTON_SIZE.y*3;
                } else if (i == 1) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*4 : BUTTON_SIZE.y*5;
                } else if (i == 2) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*8 : BUTTON_SIZE.y*9;
                }
                break;
            case MenuType::Respawn:
                if (i == 1) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*4 : BUTTON_SIZE.y*5;
                } else if (i == 2) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*8 : BUTTON_SIZE.y*9;
                } else {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*6 : BUTTON_SIZE.y*7;
                }
                break;
            case MenuType::GameOver:
                if (i == 0) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*0 : BUTTON_SIZE.y*1;
                } else if (i == 1) {
                    texturePosY = (i == this->currentButton) ? BUTTON_SIZE.y*8 : BUTTON_SIZE.y*9;
                }
                break;
        }
        this->buttons[i]->setTexture(*this->texture);
        this->buttons[i]->setTextureRect({0, texturePosY, BUTTON_SIZE.x, BUTTON_SIZE.y});
    }
}

sf::Vector2i Menu::getSize() const {
    sf::Vector2i size;
    size.x = BUTTON_SIZE.x;
    size.y = (int)(BUTTON_SIZE.y*this->buttonsSize + SPACE*(this->buttonsSize - 1));
    return size;
}

void Menu::toggleNext() {
    this->currentButton += 1;
    if (this->currentButton >= this->buttonsSize) {
        this->currentButton = 0;
    }
    this->updateSelection();
    this->switchSound->play();
}

void Menu::togglePrevious() {
    if (this->currentButton == 0) {
        this->currentButton = this->buttonsSize - 1;
    } else {
        this->currentButton -= 1;
    }
    this->updateSelection();
    this->switchSound->play();
}

unsigned int Menu::getSelection() const {
    return this->currentButton;
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (int i = 0; i < this->buttonsSize; i++) {
        target.draw(*this->buttons[i], states);
    }
}
