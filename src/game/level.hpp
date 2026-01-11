#pragma once
#include "../core/graphics.hpp"
#include "tilemap.hpp"
#include "gameobject.hpp"
#include "player.hpp"
#include "camera.hpp"

class Level {
public:
    Level();
    Level(GameObject *player, Tilemap *mainTilemap);
    ~Level() {};
    virtual void initialize(Graphics &graphics);
    virtual void update();
    virtual void render(Graphics &graphics);
public:
    Camera m_camera;
    Tilemap *m_mainTilemap;
    GameObject *m_player;
    std::vector<GameObject*> m_bullets;
    std::vector<GameObject*> m_gameObjects;
private:
    
};