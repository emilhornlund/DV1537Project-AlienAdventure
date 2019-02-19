/**
 * @file TileMap.hpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_TILEMAP_HPP
#define ALIENADVENTURE_TILEMAP_HPP

#include <Core/IEntity.hpp>

#include <SFML/Graphics/VertexArray.hpp>

#include <string>

namespace CGL { //CoreGameLib
    class IGame;
}

namespace AA { //AlienAdventure
    class TileMap : public CGL::IEntity {
    private:
        std::string name;

        unsigned int columns;

        unsigned int rows;

        unsigned int tileWidth;

        unsigned int tileHeight;

        unsigned int tilesetColumns;

        unsigned int tilesetRows;

        std::string filename;

        std::vector<int> data;

        sf::VertexArray vertices;

        TileMap(const TileMap &original);

        TileMap &operator=(const TileMap &original);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    public:
        explicit TileMap(CGL::IGame *game);

        ~TileMap() override;

        std::string getName() const;

        unsigned int getColumns() const;

        unsigned int getRows() const;

        unsigned int getTileWidth() const;

        unsigned int getTileHeight() const;

        unsigned int getTilesetColumns() const;

        unsigned int getTilesetRows() const;

        std::string getFilename() const;

        std::vector<int> getData() const;

        void setName(const std::string &name);

        void setColumns(const unsigned int columns);

        void setRows(const unsigned int rows);

        void setTileWidth(const unsigned int tileWidth);

        void setTileHeight(const unsigned int tileHeight);

        void setTilesetColumns(const unsigned int tilesetColumns);

        void setTilesetRows(const unsigned int tilesetRows);

        void setFilename(const std::string &filename);

        void setData(const std::vector<int> &data);

        void generate();

        void setColor(const sf::Color &color) override;
    };
}

#endif /* ALIENADVENTURE_TILEMAP_HPP */
