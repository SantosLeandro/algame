#pragma once

#include <vector>

class Graphics;
class Texture;
class GameObject;

class Tilemap {
public:
    Tilemap();
    Tilemap(std::vector<std::vector<int>> tiles, Texture* tileset, int tileWidth, int tileHeight);
    ~Tilemap();
    bool loadFromFile(const char* filename, Texture* tileset, int tileWidth, int tileHeight);
    void render(Graphics &graphics, int offsetX, int offsetY);
    bool checkCollision(GameObject &obj);
    bool isSolidTile(int tileX, int tileY) const {
        if (tileY < 0 || tileY >= m_mapHeight || tileX < 0 || tileX >= m_mapWidth)
            return false;
        return m_tiles[tileY][tileX] > 0;
    }

    void processCollision(GameObject &obj);
    bool getTile(int x, int y) const {
        int tx = x / m_tileWidth;
        int ty = y / m_tileHeight;
        return m_tiles[ty][tx] != 0;
    }
    bool rectCollides(int x, int y, int w, int h);
    void setTexture(Texture* texture) { m_tileset = texture; }
    void setData(const std::vector<std::vector<int>>& data) { m_tiles = data; 
        m_mapHeight = data.size();
        m_mapWidth = data.empty() ? 0 : data[0].size();
    }
    void setTileSize(int tileWidth, int tileHeight) {
        m_tileWidth = tileWidth;
        m_tileHeight = tileHeight;
    }
    int getTileWidth() const { return m_tileWidth; }
    int getTileHeight() const { return m_tileHeight; }
    int getMapWidth() const { return m_mapWidth; }
    int getMapHeight() const { return m_mapHeight; }
    void setMapSize(int width, int height) {
        m_mapWidth = width;
        m_mapHeight = height;
    }
private:
    Texture* m_tileset;
    int m_tileWidth;
    int m_tileHeight;
    int m_mapWidth;
    int m_mapHeight;
    std::vector<std::vector<int>> m_tiles;
};

