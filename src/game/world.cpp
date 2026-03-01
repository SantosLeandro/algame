#include "world.hpp"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

World::World()
{
}

World::~World()
{
}

void World::initialize(Graphics &graphics)
{
    m_camera.setTarget(m_player);
    m_camera.setWidth(graphics.getVirualResolutionWidth());
    m_camera.setHeight(graphics.getVirualResolutionHeight());
    m_camera.minPosition.x = m_currentRoom->position.x;
    m_camera.minPosition.y = m_currentRoom->position.y;
    m_camera.setMaxWidth(m_currentRoom->tilemap->getMapWidth() * m_currentRoom->tilemap->getTileWidth());
    m_camera.setMaxHeight(m_currentRoom->tilemap->getMapHeight() * m_currentRoom->tilemap->getTileHeight());
}

void World::update()
{
    if (!m_player)
        return;

    m_player->update();

    // detectar room do player
    Room* newRoom = getRoomFromPlayerPosition(m_player->getPosition());

    if (newRoom && newRoom != m_currentRoom)
    {
        m_currentRoom = newRoom;
        m_camera.minPosition.x = m_currentRoom->position.x;
        m_camera.minPosition.y = m_currentRoom->position.y;
        m_camera.setMaxWidth(m_currentRoom->tilemap->getMapWidth() * m_currentRoom->tilemap->getTileWidth());
        m_camera.setMaxHeight(m_currentRoom->tilemap->getMapHeight() * m_currentRoom->tilemap->getTileHeight());
    }

   // converter player para espaço da room
    Vector2 worldPos = m_player->getPosition();
    Vector2 localPos = worldPos - m_currentRoom->position;

    m_player->setPosition(localPos);

    m_currentRoom->tilemap->processCollision(*m_player);

    // voltar para espaço do mundo
    m_player->setPosition(m_player->getPosition() + m_currentRoom->position);

    // aplicar movimento final
    m_player->setPosition(
        m_player->getPosition() + m_player->getVelocity()
    );

    if (m_currentRoom)
    {
        for (auto &go : m_currentRoom->gameObjects)
        {
            go->update();
        }
    }
}

void World::render(Graphics &graphics)
{
    m_camera.update();
    if (!m_currentRoom)
        return;

    if (m_currentRoom->tilemap) {
        m_currentRoom->tilemap->render(graphics,m_currentRoom->position.x,m_currentRoom->position.y);
    }
        

    for (auto &go : m_currentRoom->gameObjects)
    {
        go->render(graphics);
    }

    if (m_player)
        m_player->render(graphics);
}

void World::loadRoomFromFile(const std::string &file, TextureManager *texturemanager)
{
    std::ifstream f(file);
    if (!f.is_open())
        return;

    json j;
    f >> j;

    auto rooms = j["room"];

    for (auto &r : rooms)
    {
        auto room = std::make_unique<Room>();

        room->name = r["name"].get<std::string>();
        room->width = r["width"].get<int>();
        room->height = r["height"].get<int>();
        room->tilesize = r["tilesize"].get<int>();

        room->position.x = r["x"].get<int>();
        room->position.y = r["y"].get<int>();

        

        auto layers = r["layer"];
        for (auto &layer : layers)
        {

            std::string texture = layer["texture"].get<std::string>();
            std::string data = layer["data"].get<std::string>();

            auto tiles = parseTileData(data, layer["width"].get<int>(), layer["height"].get<int>());

            room->tilemap = std::make_unique<Tilemap>(
                tiles,
                texturemanager->get("texture//"+texture),
                room->tilesize,
                room->tilesize);

            // room->tilemap->load(
            //     texture,
            //     data,
            //     layer["width"].get<int>(),
            //     layer["height"].get<int>()
            // );

            auto gameObjects = layer["gameobject"];
            for (auto &go : gameObjects)
            {
                std::string name = go["name"].get<std::string>();
                int x = go["x"].get<int>()+room->position.x;
                int y = go["y"].get<int>()+room->position.y;

                if (name == "player")
                {
                    if (!m_player)
                        //Texture *tex = texturemanager->get("texture//samus.png");
                        m_player = new Player(Vector2(x,y), texturemanager->get("texture//samus.png"));

                    m_player->setPosition(Vector2(x, y));
                }
                else
                {
                    auto obj = std::make_unique<GameObject>();
                    obj->setName(name);
                    obj->setPosition(Vector2(x, y));

                    room->gameObjects.push_back(std::move(obj));
                }
            }
        }

        if (!m_currentRoom)
            m_currentRoom = room.get();

        m_rooms[room->name] = std::move(room);
    }
}

Room* World::getRoomFromPlayerPosition(const Vector2& pos)
{
    if (!m_player)
        return nullptr;

    Box box = m_player->getBoundingBox();
    Vector2 playerPos = m_player->getPosition();

    int left   = playerPos.x + box.x;
    int right  = left + box.w;
    int top    = playerPos.y + box.y;
    int bottom = top + box.h;

    for (auto &pair : m_rooms)
    {
        Room* room = pair.second.get();

        int worldLeft   = room->position.x;
        int worldRight  = room->position.x + room->width * room->tilesize;
        int worldTop    = room->position.y;
        int worldBottom = room->position.y + room->height * room->tilesize;

        // verifica se qualquer parte do player está dentro da room
        if (right > worldLeft &&
            left < worldRight &&
            bottom > worldTop &&
            top < worldBottom)
        {
            return room;
        }
    }

    return nullptr;
}

Room* World::getRoom(const std::string& name)
{
    auto it = m_rooms.find(name);
    if (it != m_rooms.end())
        return it->second.get();

    return nullptr;
}

Room* World::getCurrentRoom()
{
    return m_currentRoom;
}

void World::setCurrentRoom(const std::string &room)
{
    m_currentRoom = m_rooms[room].get();
}

static std::vector<std::vector<int>> parseTileData(
    const std::string& data,
    int width,
    int height)
{
    std::vector<std::vector<int>> tiles(height, std::vector<int>(width));

    std::stringstream ss(data);
    std::string item;

    int index = 0;

    while (std::getline(ss, item, ','))
    {
        int value = std::stoi(item);

        int x = index % width;
        int y = index / width;

        if (y < height)
            tiles[y][x] = value;

        index++;
    }

    return tiles;
}