#pragma once

#include "../core/graphics.hpp"
#include "../core/texturemanager.hpp"
#include "tilemap.hpp"
#include "gameobject.hpp"
#include "player.hpp"
#include "camera.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

struct Room
{
    std::string name;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::unique_ptr<Tilemap> tilemap;

    Vector2 position;
    int width = 0;
    int height = 0;
    int tilesize = 16;
};

class World
{
public:
    World();
    ~World();

    void initialize(Graphics &graphics);
    void update();
    void render(Graphics &graphics);

    void loadRoomFromFile(const std::string &file, TextureManager *texturemanager);
    Room* getRoomFromPlayerPosition(const Vector2& pos);
    Room* getRoom(const std::string& name);
    Room* getCurrentRoom();
    void setCurrentRoom(const std::string &room);

public:
    Camera m_camera;

private:
    std::unordered_map<std::string, std::unique_ptr<Room>> m_rooms;

    Room* m_currentRoom = nullptr;
    Player* m_player;
    bool m_roomTransition = false;
};

static std::vector<std::vector<int>> parseTileData(
    const std::string& data,
    int width,
    int height);