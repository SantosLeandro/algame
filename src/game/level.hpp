#pragma once
#include "../core/graphics.hpp"
#include "tilemap.hpp"
#include "gameobject.hpp"
#include "player.hpp"
// #include "door.hpp"
#include "camera.hpp"

class Level {
public:
    Level();
    Level(GameObject *player, Tilemap *mainTilemap);
    ~Level() {};
    virtual void initialize(Graphics &graphics);
    virtual void update();
    virtual void render(Graphics &graphics);
    void addGameObject(GameObject *go);
    void setCameraTarget(GameObject *target);
    Camera& getCamera() { return m_camera; }
    bool checkCollision(GameObject &a, GameObject &b);
    GameObject* getPlayer() { return m_player; }
    GameObject* getGameObjectByTag(const std::string& tag) {
        for (auto &go : m_gameObjects) {
            if (go->getTag() == tag) {
                return go;
            }
        }
        return nullptr;
    }
    GameObject* getGameObjectByName(const std::string& name) {
        for (auto &go : m_gameObjects) {
            if (go->getName() == name) {
                return go;
            }
        }
        return nullptr;
    }

    void transition();

public:
    bool m_transitioning = false;
    int duration = 500;
    int elapsed = 0;
    Camera m_camera;
    Tilemap *m_mainTilemap;
    GameObject *m_player;
    std::vector<GameObject*> m_bullets;
    std::vector<GameObject*> m_gameObjects;
    std::vector<GameObject*> m_doors;
private:
    
};