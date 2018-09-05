//
// Created by Emil Hörnlund on 2018-09-02.
//

#ifndef ALIENADVENTURE_CORE_HPP
#define ALIENADVENTURE_CORE_HPP

class AnimationFrame;
class AnimationHandler;
class AnimationSequence;
class Background;
class Collectible;
class CollectibleCoin;
class CollectibleHealth;
class Enemy;
class EventHandler;
class Game;
class GameObject;
class Hud;
class LevelHandler;
class Menu;
class ObjectHandler;
class Player;
class Renderer;
class StaticFrame;
class TileMap;
class World;

namespace sf {
    class Music;
    class Texture;
    class SoundBuffer;
    class Image;
}

// Forward declaration and a few type definitions
template <typename Resource>
class ResourceHandler;
typedef ResourceHandler<sf::Image> ImageResourceHandler;
typedef ResourceHandler<sf::Music> MusicResourceHandler;
typedef ResourceHandler<sf::SoundBuffer> SoundBufferResourceHandler;
typedef ResourceHandler<sf::Texture> TextureResourceHandler;

#endif //ALIENADVENTURE_CORE_HPP
