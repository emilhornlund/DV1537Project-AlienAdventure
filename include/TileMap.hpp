/**
 * @file TileMap.hpp
 * @date 2016-11-29
 * @author Emil Hörnlund
 */

#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "Core.hpp"
#include "StaticFrame.hpp"

class TileMap : public StaticFrame {
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
public:
    TileMap(Game *game);

    TileMap(const TileMap &original);

    ~TileMap() override;

    virtual TileMap& operator=(const TileMap &original);

    TileMap* clone() const override;

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

    void setData(const std::vector<int> data);

    void generate();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* TileMap_hpp */
