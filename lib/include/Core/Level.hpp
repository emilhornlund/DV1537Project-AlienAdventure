//
// Created by Emil Hörnlund on 2018-09-15.
//

#ifndef COREGAMELIB_LEVEL_HPP
#define COREGAMELIB_LEVEL_HPP

#include <SFML/System/Vector2.hpp>
#include <tinyxml2.h>

#include <string>
#include <vector>

namespace CGL { //CoreGameLib
    class Level {
    public:
        struct Tileset {
            struct Image {
                std::string source;
                sf::Vector2i size;
            };
            std::string name;
            int firstgid, tilecount, columns;
            sf::Vector2i tileSize;
            Image image;
        };

        struct Layer {
            std::string name;
            sf::Vector2i size;
            std::vector<int> data;
        };
    private:
        sf::Vector2i m_tiles;

        sf::Vector2i m_tileSize;

        sf::Vector2i m_mapSize;

        std::vector<Level::Tileset> m_tilesets;

        std::vector<Level::Layer> m_layers;

        Level(const Level &original);

        Level &operator=(const Level &original);

        void parseMap(const tinyxml2::XMLElement *root);

        void parseTileset(const tinyxml2::XMLElement *element);

        void parseLayer(const tinyxml2::XMLElement *element);
    public:
        Level();

        ~Level();

        bool loadFromFile(const std::string &filename);

        const sf::Vector2i &getNumberOfTiles() const;

        const sf::Vector2i &getTileSize() const;

        const sf::Vector2i &getMapSize() const;

        const std::vector<Level::Tileset> &getTilesets() const;

        const std::vector<Level::Layer> &getLayers() const;
    };
}

#endif //COREGAMELIB_LEVEL_HPP
