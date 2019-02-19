#include <utility>

#include <utility>

#include <utility>

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
    class Level;

    typedef std::shared_ptr<const Tileset> TilesetPtr;
    typedef std::shared_ptr<const Tilelayer> TilelayerPtr;

    struct Object {
    public:
        unsigned int id;
        std::string name;
        std::string type;
        sf::Vector2i position;
        sf::Vector2i size;

        Object(const unsigned int id, std::string name, std::string type, const sf::Vector2i position,
               sf::Vector2i size) : id(id), name(std::move(name)), type(std::move(type)), position(position), size(size) {}
    };

    typedef std::shared_ptr<const Object> ObjectPtr;

    struct ObjectGroup {
    public:
        unsigned int id;
        std::string name;
        std::vector<ObjectPtr> objects;

        ObjectGroup(const unsigned int id, std::string name,
                    std::vector<std::shared_ptr<const Object>> objects) : id(id), name(std::move(name)), objects(std::move(objects)) {}
    };

    typedef std::shared_ptr<const ObjectGroup> ObjectGroupPtr;

    class Level : private sf::NonCopyable {
    private:
        sf::Vector2i m_tileSize;

        sf::Vector2i m_mapSize;

        std::vector<TilesetPtr> m_tilesets;

        std::vector<TilelayerPtr> m_tilelayers;

        std::vector<ObjectGroupPtr> m_objectGroups;

        bool parseTilesets(const tinyxml2::XMLElement *node);

        bool parseTilelayers(const tinyxml2::XMLElement *node);

        bool parseObjectGroups(const tinyxml2::XMLElement *node);

        const std::vector<std::shared_ptr<const Object>> parseObjects(const tinyxml2::XMLElement *node);
    public:
        Level() = default;

        virtual ~Level() = default;

        bool loadFromFile(const std::string &filename);

        sf::Vector2i getTileSize() const;

        sf::Vector2i getMapSize() const;

        const std::vector<TilesetPtr>& getTilesets() const;

        const std::vector<TilelayerPtr>& getTilelayers() const;

        const std::vector<ObjectGroupPtr>& getObjectGroups() const;

        const std::vector<TilesetPtr> getUsedTilesets(TilelayerPtr tilelayerPtr) const;

        const std::vector<int> getTileData(TilelayerPtr tilelayerPtr, TilesetPtr tilesetPtr) const;
    };
}

#endif //COREGAMELIB_LEVEL_HPP
