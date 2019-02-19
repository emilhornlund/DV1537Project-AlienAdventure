//
// Created by Emil Hörnlund on 2018-09-15.
//

#ifndef COREGAMELIB_LEVEL_HPP
#define COREGAMELIB_LEVEL_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <vector>
#include <memory>

namespace tinyxml2 { //TinyXML2
    class XMLElement;
}

namespace CGL { //CoreGameLib
    class Tilelayer;
    class Tileset;

    typedef std::shared_ptr<const Tileset> TilesetPtr;
    typedef std::shared_ptr<const Tilelayer> TilelayerPtr;

    class Level : private sf::NonCopyable {
    private:
        sf::Vector2i m_tileSize;

        sf::Vector2i m_mapSize;

        std::vector<TilesetPtr> m_tilesets;

        std::vector<TilelayerPtr> m_tilelayers;

        bool parseTilesets(const tinyxml2::XMLElement *node);

        bool parseTilelayers(const tinyxml2::XMLElement *node);

        bool parseObjects(const tinyxml2::XMLElement *node);
    public:
        Level() = default;

        virtual ~Level() = default;

        bool loadFromFile(const std::string &filename);

        sf::Vector2i getTileSize() const;

        sf::Vector2i getMapSize() const;

        const std::vector<TilesetPtr>& getTilesets() const;

        const std::vector<TilelayerPtr>& getTilelayers() const;

        const std::vector<TilesetPtr> getUsedTilesets(TilelayerPtr tilelayerPtr) const;

        const std::vector<int> getTileData(TilelayerPtr tilelayerPtr, TilesetPtr tilesetPtr) const;
    };
}

#endif //COREGAMELIB_LEVEL_HPP
