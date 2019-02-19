//
// Created by Emil Hörnlund on 2019-02-19.
//

#ifndef COREGAMELIB_TILELAYER_HPP
#define COREGAMELIB_TILELAYER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <vector>

namespace tinyxml2 { //TinyXML2
    class XMLElement;
}

namespace CGL { //CoreGameLib
    class Tilelayer final : sf::NonCopyable {
    private:
        std::string m_name;

        sf::Vector2i m_layerSize;

        std::vector<int> m_tiles;

        bool parseTileData(const tinyxml2::XMLElement *node);
    public:
        Tilelayer(const std::string &name, const sf::Vector2i &layerSize);

        explicit Tilelayer(const tinyxml2::XMLElement *node);

        ~Tilelayer() = default;

        std::string getName() const;

        sf::Vector2i getLayerSize() const;

        const std::vector<int>& getTiles() const;

        int getTile(const int x, const int y) const;
    };
}

#endif //COREGAMELIB_TILELAYER_HPP
