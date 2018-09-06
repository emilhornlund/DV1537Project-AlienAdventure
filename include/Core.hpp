//
// Created by Emil Hörnlund on 2018-09-02.
//

#ifndef ALIENADVENTURE_CORE_HPP
#define ALIENADVENTURE_CORE_HPP

class AnimationFrame;
class AnimationHandler;
class AnimationSequence;
class Background;
class Camera;
class Collectible;
class CollectibleCoin;
class CollectibleHealth;
class Enemy;
class EnemyBee;
class EnemyBeeBlack;
class EnemyFishBlue;
class EnemyFishGreen;
class EnemyFishPink;
class EnemyFrog;
class EnemyMouse;
class EnemySlimeBlue;
class EnemySlimeGreen;
class EnemySlimePurple;
class EnemySnail;
class EnemySnailMushroom;
class EnemyWormGreen;
class EnemyWormPink;
class EventHandler;
class Game;
class GameObject;
class Hud;
class LevelHandler;
class Menu;
class ObjectHandler;
class Player;
class StaticFrame;
class TileMap;
class WindowHandler;
class World;

namespace sf {
    class Music;
    class Texture;
    class SoundBuffer;
    class Image;
    class Sound;
}

// Forward declaration and a few type definitions
template <typename Resource>
class ResourceHandler;
typedef ResourceHandler<sf::Image> ImageResourceHandler;
typedef ResourceHandler<sf::Music> MusicResourceHandler;
typedef ResourceHandler<sf::SoundBuffer> SoundBufferResourceHandler;
typedef ResourceHandler<sf::Texture> TextureResourceHandler;

#endif //ALIENADVENTURE_CORE_HPP
