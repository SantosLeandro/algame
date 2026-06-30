#include "world.hpp"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

World::World()
{
    m_player = nullptr;
}

World::~World()
{
}

void World::initialize(Graphics &graphics)
{
    std::cout << "Initializing world" << std::endl;
    m_camera.setTarget(m_player);
    m_camera.setWidth(graphics.getVirualResolutionWidth());
    m_camera.setHeight(graphics.getVirualResolutionHeight());
    if (!m_currentRoom) return;
    m_camera.minPosition.x = m_currentRoom->position.x;
    m_camera.minPosition.y = m_currentRoom->position.y;
    if (m_currentRoom->m_layers.find("Ground") != m_currentRoom->m_layers.end()) {
        m_camera.setMaxWidth(m_currentRoom->m_layers["Ground"]->getMapWidth() * m_currentRoom->m_layers["Ground"]->getTileWidth());
        m_camera.setMaxHeight(m_currentRoom->m_layers["Ground"]->getMapHeight() * m_currentRoom->m_layers["Ground"]->getTileHeight());
    }
    std::cout << "Finished initializing world" << std::endl;
}

void World::update()
{
    if (!m_player)
        return;


    if(m_camera.isFollowingTarget()){
        m_roomTransition = false;
    }

    //if(!m_roomTransition)
    m_player->update();

    // detectar room do player
    Room* newRoom = getRoomFromPlayerPosition(m_player->getPosition());

    if(newRoom && newRoom != m_currentRoom)
    {
        std::cout << "Player moved to new room: " << newRoom->name << std::endl;
    }


    if (newRoom && newRoom != m_currentRoom)
    {
        std::cout << "Transitioning to new room: " << newRoom->name << std::endl;
        
        setCurrentRoom(newRoom->name);
        // m_currentRoom = newRoom;
        m_camera.minPosition.x = m_currentRoom->position.x;
        m_camera.minPosition.y = m_currentRoom->position.y;
        if (m_currentRoom->m_layers.find("Ground") != m_currentRoom->m_layers.end()) {
            m_camera.setMaxWidth(m_currentRoom->m_layers["Ground"]->getMapWidth() * m_currentRoom->m_layers["Ground"]->getTileWidth());
            m_camera.setMaxHeight(m_currentRoom->m_layers["Ground"]->getMapHeight() * m_currentRoom->m_layers["Ground"]->getTileHeight());
        }

        // centro da nova room
        int signX = (m_player->getPosition().x > m_currentRoom->position.x) ? 1 : -1;
        int signY = (m_player->getPosition().y > m_currentRoom->position.y) ? 1 : -1;
        Vector2 center;
        center.x = m_player->getPosition().x;

        center.y = m_player->getPosition().y;

        m_camera.moveTo(center);
        m_roomTransition = true;
    }

    //if(!m_roomTransition) {
    // converter player para espaço da room
        Vector2 worldPos = m_player->getPosition();
        Vector2 localPos = worldPos - m_currentRoom->position;

        m_player->setPosition(localPos);

        if (m_currentRoom->m_layers.find("Ground") != m_currentRoom->m_layers.end()) {
            m_currentRoom->m_layers["Ground"]->processCollision(*m_player);
        }

        // voltar para espaço do mundo
        m_player->setPosition(m_player->getPosition() + m_currentRoom->position);

        // aplicar movimento final
        // m_player->setPosition(
        //     m_player->getPosition() + m_player->getVelocity()
        // );
    //}

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

    for (auto &layer : m_currentRoom->m_layers) {
        if (layer.second) {
            layer.second->render(graphics, m_currentRoom->position.x, m_currentRoom->position.y);
        }
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

    std::cout << "Loading world from file: " << file << std::endl;
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

            std::cout << "Creating tilemap for room: " << room->name << std::endl;
            std::cout << "Tilemap size: " << tiles[0].size() << "x" << tiles.size() << std::endl;
            std::cout << "Using texture: " << texture << std::endl;


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

            std::cout << gameObjects.size() << " game objects found in layer" << std::endl;
            for (auto &go : gameObjects)
            {
                std::string name = go["name"].get<std::string>();
                int x = go["x"].get<int>()+room->position.x;
                int y = go["y"].get<int>()+room->position.y;

                if (name == "player")
                {
                    if (!m_player)
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

    std::cout << "Finished loading world from file: " << file << std::endl;
}

void World::loadFromSnapFile(const std::string &file, TextureManager *texturemanager, GameObjectFactory &factory)
{
    std::cout << "Loading world from snap file: " << file << std::endl;
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cerr << "Failed to open snap file: " << file << std::endl;
        return;
    }

    json j;
    f >> j;

    int defaultTileSize = j.value("defaultTileSize", 16);

    auto &rooms = j["rooms"];
    for (auto &r : rooms) {
        auto room = std::make_unique<Room>();

        room->name = r["name"].get<std::string>();
        room->width = r["width"].get<int>();
        room->height = r["height"].get<int>();
        room->tilesize = defaultTileSize;
        room->position.x = r.value("x", 0);
        room->position.y = r.value("y", 0);

        std::cout << "Loading room: " << room->name << " at position (" << room->position.x << ", " << room->position.y << ")" << std::endl;

        auto &layers = r["layers"];
        for (auto &layer : layers) {
            if (!layer.value("visible", true))
                continue;

            std::string tileset = layer.value("tileset", "");

            std::cout << "Loading layer: " << layer.value("name", "") << " with tileset: " << tileset << std::endl;

            if (!tileset.empty()) {
                std::string tilesData = layer["tiles"].get<std::string>();
                auto tiles = parseTileData(tilesData, room->width, room->height);


                //fix temporario pegar o nome do arquivo sem assets
               
                tileset = tileset.substr(7);
                

                std::string texKey = "texture//" + tileset;

                std::cout << "Loading tileset texture: " << texKey << std::endl;

                Texture *tex = texturemanager->get(texKey);
                if (!tex) {
                    texturemanager->load(texKey);
                    tex = texturemanager->get(texKey);
                }

                auto tilemap = std::make_unique<Tilemap>(
                    tiles, tex, room->tilesize, room->tilesize
                );

                //se o layer for ground, setar o tilemap como tilemap principal da room


        
                room->m_layers[layer.value("name", "")] = std::move(tilemap);
            
            }

            if (layer.contains("objects")) {
                for (auto &obj : layer["objects"]) {
                    std::string type = obj["type"].get<std::string>();
                    int x = obj["x"].get<int>() + room->position.x;
                    int y = obj["y"].get<int>() + room->position.y;

                    if (type == "player") {
                        std::cout << "Setting player position to: (" << x << ", " << y << ")" << std::endl;
                        if (!m_player) {
                            m_player = new Player(Vector2(x, y), texturemanager->get("texture//samus.png"));
                        }
                        m_player->setPosition(Vector2(x, y));
                    } else {
                        auto *gameObj = factory.create(type, Vector2(x, y), *texturemanager);
                        if (obj.contains("name"))
                            gameObj->setName(obj["name"].get<std::string>());
                        else
                            gameObj->setName(type);
                        gameObj->setPosition(Vector2(x, y));
                        room->gameObjects.push_back(std::unique_ptr<GameObject>(gameObj));
                    }
                }
            }
        }

        if (!m_currentRoom)
            m_currentRoom = room.get();

        m_rooms[room->name] = std::move(room);
    }

    std::cout << "Finished loading snap file: " << file << std::endl;
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