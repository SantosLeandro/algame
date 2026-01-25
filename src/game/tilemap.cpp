#include "tilemap.hpp"
#include "../core/graphics.hpp"
#include "../core/texture.hpp"
#include "gameobject.hpp"

Tilemap::Tilemap()
{
}

Tilemap::Tilemap(std::vector<std::vector<int>> tiles, Texture *tileset, int tileWidth, int tileHeight)
{
    m_tiles = tiles;
    m_tileset = tileset;
    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;
    m_mapHeight = tiles.size();
    m_mapWidth = tiles.empty() ? 0 : tiles[0].size();
}

Tilemap::~Tilemap()
{
}

bool Tilemap::loadFromFile(const char *filename, Texture *tileset, int tileWidth, int tileHeight)
{
    return false;
}

void Tilemap::render(Graphics &graphics, int offsetX, int offsetY)
{
    for (int y = 0; y < m_mapHeight; y++)
    {
        for (int x = 0; x < m_mapWidth; x++)
        {
            int tileIndex = m_tiles[y][x];
            int sx = (tileIndex % (m_tileset->getWidth() / m_tileWidth)) * m_tileWidth;
            int sy = (tileIndex / (m_tileset->getWidth() / m_tileWidth)) * m_tileHeight;
            int dx = x * m_tileWidth + offsetX;
            int dy = y * m_tileHeight + offsetY;
            graphics.drawTextureRegion(m_tileset, sx, sy, m_tileWidth, m_tileHeight, dx, dy, 0);
        }
    }
}

void Tilemap::processCollision(GameObject &obj)
{
    obj.setOnGround(false);
    int w = obj.getBoundingBox().w;
    int h = obj.getBoundingBox().h;
    if(rectCollides(obj.getPosition().x + obj.getBoundingBox().x,
                    obj.getPosition().y + obj.getBoundingBox().y + obj.getVelocity().y,
                    w,
                    h))
    {
        int sign = (obj.getVelocity().y > 0) ? 1 : -1;
        for(int i=0; i < abs(obj.getVelocity().y); i++)
        {
            if(rectCollides(obj.getPosition().x + obj.getBoundingBox().x,
                             obj.getPosition().y + obj.getBoundingBox().y - sign,
                             w,
                             h))
            {
                obj.setPosition(Vector2(
                    obj.getPosition().x,
                    obj.getPosition().y - sign
                ));
            }
            else
            {
                obj.setOnGround(sign > 0); // opcional
                obj.setVelocity(Vector2(obj.getVelocity().x, 0));
                break;
            }
        }
    }

    if(rectCollides(obj.getPosition().x + obj.getBoundingBox().x + obj.getVelocity().x,
                    obj.getPosition().y + obj.getBoundingBox().y,
                    w,
                    h))
    {
       
        int sign = (obj.getVelocity().x > 0) ? 1 : -1;
        for(int i=0; i < abs(obj.getVelocity().x); i++)
        {
            if(!rectCollides(obj.getPosition().x + obj.getBoundingBox().x + sign,
                             obj.getPosition().y + obj.getBoundingBox().y,
                             w,
                             h))
            {
                obj.setPosition(Vector2(
                    obj.getPosition().x + sign,
                    obj.getPosition().y
                ));
            }
            else
            { 
                obj.setVelocity(Vector2(0, obj.getVelocity().y));
                obj.onTileCollision(1,sign,0);
                break;
            }
        }
    }
    
}

bool Tilemap::rectCollides(int x, int y, int w, int h)
{
    int left   = x / m_tileWidth;
    int right  = (x + w - 1) / m_tileWidth;
    int top    = y / m_tileHeight;
    int bottom = (y + h - 1) / m_tileHeight;

    for (int ty = top; ty <= bottom; ty++)
    {
        for (int tx = left; tx <= right; tx++)
        {
            if (isSolidTile(tx, ty) > 0)
                return true;
        }
    }
    return false;
}


bool Tilemap::checkCollision(GameObject& obj)
{
    bool collided = false;

    Vector2 pos = obj.getPosition();
    Vector2 vel = obj.getVelocity();
    auto box = obj.getBoundingBox();

    /* =====================
       EIXO X
       ===================== */
    pos.x += vel.x;

    if (rectCollides(pos.x + box.x, pos.y + box.y, box.w, box.h))
    {
        if (vel.x > 0) // direita
        {
            int tileX = (pos.x + box.x + box.w) / m_tileWidth;
            pos.x = tileX * m_tileWidth - box.x - box.w;
        }
        else if (vel.x < 0) // esquerda
        {
            int tileX = (pos.x + box.x) / m_tileWidth;
            pos.x = (tileX + 1) * m_tileWidth - box.x;
        }

        vel.x = 0;
        collided = true;
    }

    /* =====================
       EIXO Y
       ===================== */
    pos.y += vel.y;

    if (rectCollides(pos.x + box.x, pos.y + box.y, box.w, box.h))
    {
        if (vel.y > 0) // caindo
        {
            int tileY = (pos.y + box.y + box.h) / m_tileHeight;
            pos.y = tileY * m_tileHeight - box.y - box.h;
            obj.setOnGround(true); // opcional
        }
        else if (vel.y < 0) // batendo a cabeça
        {
            int tileY = (pos.y + box.y) / m_tileHeight;
            pos.y = (tileY + 1) * m_tileHeight - box.y;
        }

        vel.y = 0;
        collided = true;
    }
    else
    {
        obj.setOnGround(false); // opcional
    }

    obj.setPosition(pos);
    obj.setVelocity(vel);
    return collided;
}
