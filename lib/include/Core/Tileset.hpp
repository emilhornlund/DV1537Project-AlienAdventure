//
// Created by Emil Hörnlund on 2019-02-19.
//

#ifndef COREGAMELIB_TILESET_HPP
#define COREGAMELIB_TILESET_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

namespace tinyxml2 { //TinyXML2
    class XMLElement;
}

namespace CGL { //CoreGameLib
    class Tileset final : sf::NonCopyable {
    private:
        std::string m_name;

        std::string m_source;

        int m_firstGID;

        sf::Vector2i m_tileSize;

        unsigned int m_spacing;

        unsigned int m_tileCount;

        unsigned int m_columns;

        unsigned int m_rows;
    public:
        Tileset(const std::string &name, const std::string &source, const int firstGID, const sf::Vector2i &tileSize,
                const unsigned int spacing, const unsigned int tileCount, const unsigned int columns);

        explicit Tileset(const tinyxml2::XMLElement *node);

        ~Tileset() = default;

        std::string getName() const;

        std::string getSource() const;

        int getFirstGID() const;

        sf::Vector2i getTileSize() const;

        unsigned int getSpacing() const;

        unsigned int getTileCount() const;

        unsigned int getColumns() const;

        unsigned int getRows() const;
    };
}

#endif //COREGAMELIB_TILESET_HPP
