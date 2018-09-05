/**
 * @file Renderer.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#include "AnimationFrame.hpp"
#include "AnimationHandler.hpp"
#include "AnimationSequence.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Hud.hpp"
#include "LevelHandler.hpp"
#include "Menu.hpp"
#include "Renderer.hpp"
#include "StaticFrame.hpp"

RenderItem::RenderItem(sf::Drawable* drawable, unsigned int depth) {
    this->drawable = drawable;
    this->depth = depth;
}

RenderItem::RenderItem(const RenderItem &original) {
    this->drawable = original.drawable;
    this->depth = original.depth;
}

RenderItem& RenderItem::operator=(const RenderItem &original) {
    if (this != &original) {
        this->drawable = original.getDrawable();
        this->depth = original.getDepth();
    }
    return *this;
}

RenderItem::~RenderItem() = default;;

unsigned int RenderItem::getDepth() const {
    return this->depth;
}

sf::Drawable* RenderItem::getDrawable() const {
    return this->drawable;
}

bool RenderItem::operator>(const RenderItem& original) const {
    return this->depth > original.depth;
}

bool RenderItem::operator<(const RenderItem& original) const {
    return this->depth < original.depth;
}

RenderItem* RenderItem::clone() const {
    return new RenderItem(*this);
}

Renderer::Renderer(Game *game, const sf::Vector2u windowSize, const std::string &title) {
    this->game = game;

    this->queueCapacity = 0;
    this->queueSize = 0;
    this->queue = new RenderItem*[this->queueCapacity];

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y, 32), title, sf::Style::Titlebar | sf::Style::Close);
    window->setKeyRepeatEnabled(true);

    std::string rpath = "./resources/Icon.png";
    sf::Image icon;
    if (!icon.loadFromFile(rpath)) {
        throw "Failed to load " + rpath;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    this->view = new sf::View();
    this->view->reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    window->setView(*this->view);
    this->window = window;
}

Renderer::~Renderer() {
    this->clearQueue();

    delete this->window;
    this->window = nullptr;

    delete this->view;
    this->view = nullptr;
}

void Renderer::clearQueue() {
    for (int i = 0; i < this->queueSize; i++) {
        delete this->queue[i];
        this->queue[i] = nullptr;
    }
    delete[] this->queue;
    this->queue = nullptr;
}

void Renderer::addRenderItem(sf::Drawable* drawable, unsigned int depth) {
    if (this->queueCapacity == this->queueSize) {
        this->queueCapacity += 5;
        auto **tempQueue = new RenderItem*[this->queueCapacity];
        for (int i = 0; i < this->queueSize; i++) {
            tempQueue[i] = this->queue[i]->clone();
        }
        this->clearQueue();
        this->queue = tempQueue;
    }
    this->queue[this->queueSize] = new RenderItem(drawable, depth);
    this->queueSize++;
}

void Renderer::sortQueue() {
    int i, j, flag = 1;
    RenderItem* temp;
    for(i = 1; (i <= this->queueSize) && flag; i++) {
        flag = 0;
        for (j = 0; j < (this->queueSize - 1); j++) {
            if (*this->queue[j+1] > *this->queue[j]) {
                temp = this->queue[j];
                this->queue[j] = this->queue[j+1];
                this->queue[j+1] = temp;
                flag = 1;
            }
        }
    }
};

sf::RenderWindow* Renderer::getRenderWindow() {
    return this->window;
}

sf::View* Renderer::getView() {
    return this->view;
}

void Renderer::updateCamera(const sf::Vector2f position) {
    sf::Vector2u minCenter;
    minCenter.x = this->window->getSize().x/2;
    minCenter.y = this->window->getSize().y/2;

    sf::Vector2u maxCenter;
    maxCenter.x = this->game->getLevelHandler()->getWorldSize().x - this->window->getSize().x/2;
    maxCenter.y = this->game->getLevelHandler()->getWorldSize().y - this->window->getSize().y/2;

    sf::Vector2f cameraPosition = {0, 0};

    if (position.x < minCenter.x) {
        cameraPosition.x = minCenter.x;
    } else if (position.x > maxCenter.x) {
        cameraPosition.x = maxCenter.x;
    } else {
        cameraPosition.x = position.x;
    }

    if (position.y < minCenter.y) {
        cameraPosition.y = minCenter.y;
    } else if (position.y > maxCenter.y) {
        cameraPosition.y = maxCenter.y;
    } else {
        cameraPosition.y = position.y;
    }

    this->getView()->setCenter(cameraPosition);
}

void Renderer::render() {
    this->sortQueue();

    this->window->setView(*this->view);
    this->fitViewToWindow();

    for (int i = 0; i < this->queueSize; i++) {
        this->window->draw(*queue[i]->getDrawable());
    }

    this->window->setView(this->window->getDefaultView());
    this->window->draw(*this->game->getHud());

    if (this->game->getState() != GameState::Playing) {
        this->window->setView(this->window->getDefaultView());
        if (this->game->getState() == GameState::Paused) {
            this->window->draw(*this->game->getPauseMenu());
        } else if (this->game->getState() == GameState::Respawn) {
            this->window->draw(*this->game->getRespawnMenu());
        } else if (this->game->getState() == GameState::GameOver) {
            this->window->draw(*this->game->getGameOverMenu());
        }
    }

    this->window->display();

    this->clearQueue();
    this->queueCapacity = 0;
    this->queueSize = 0;
}

void Renderer::fitViewToWindow() {
    sf::Vector2u size = this->window->getSize();
    this->view->setSize(sf::Vector2f(size.x, size.y));
}

void Renderer::clear(sf::Color color) {
    this->window->clear(color);
}

void Renderer::draw(GameObject &object) {
    AnimationHandler* animation = object.getAnimationHandler();
    if (animation != nullptr && object.isVisible()) {
        int updates = 0;
        if (animation->numberOfStaticFrames() > 0) {
            for (unsigned int i = 0; i < animation->numberOfStaticFrames(); i++) {
                StaticFrame* frame = animation->getStaticFrame(i);
                if (frame != nullptr) {
                    this->addRenderItem(frame, (unsigned int)object.getDepth());
                    updates++;
                }
            }
        }
        AnimationSequence* sequence = animation->getCurrentSequence();
        if (sequence != nullptr) {
            AnimationFrame* frame = sequence->getCurrentFrame();
            if (frame != nullptr) {
                this->addRenderItem(frame, (unsigned int)object.getDepth());
                updates++;
            }
        }
        if (updates > 0) {
            object.updateSprites();
        }
    }
}
