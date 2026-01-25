#include "maploader.hpp"

MapLoader::MapLoader(/* args */)
{
}

MapLoader::~MapLoader()
{
}
Level* MapLoader::load(const char* filename, Graphics& graphics, TextureManager &textureManager, GameObjectFactory &factory)
{
    Level* level = new Level();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo JSON\n";
        return nullptr;
    }

    json root;
    file >> root;
    std::string cameraTarget = "";
    root["tilesize"].get<int>();
    if (root.contains("options") && root["options"].is_object()) {
        const json &options = root["options"];
        if(options.contains("camera")){
            cameraTarget = options["camera"].get<std::string>();
        } else {
            std::cout << "There is no camera target in options:{camera:'target'}\n";
        }
    }

    int tilesize = root["tilesize"].get<int>();

    const json &jLayers = root["layer"];
    for (const auto &layer : jLayers)
    {
        std::string textureFilename = layer["texture"].get<std::string>();
        auto texture = textureManager.get("texture//"+textureFilename);
        if(texture == nullptr) {
            textureManager.load("texture//"+textureFilename);
            texture = textureManager.get(textureFilename);
        }
        

        int width = layer["width"].get<int>();
        int height = layer["height"].get<int>();
        std::string layerName = layer["name"].get<std::string>();

        std::string eData = layer["data"].get<std::string>();
        std::stringstream ss(eData);
        std::string token;
        std::vector<std::string> temp;

        Tilemap* tilemap = new Tilemap();
        tilemap->setTexture(texture);
        tilemap->setTileSize(tilesize, tilesize);
        tilemap->setMapSize(width, height);
        std::vector<std::vector<int>> data;
        data.reserve(height);
        for(auto &r : data) {
            r.reserve(width);
        }

        while (std::getline(ss, token, ','))
        {
            temp.push_back(token);
        }

        for (int i = 0; i < height; i++)
        {
            data.push_back(std::vector<int>());
            for (int j = 0; j < width; j++)
            {
                data[i].push_back(std::stoi(temp[(i * width) + j]));
            }
        }
        tilemap->setData(data);
        //tilemap->GetTileSlopes();
        //texture->CreateMask();
        //std::vector<std::shared_ptr<GameObject>> gameObjects;
        
        if(layer.contains("gameobject")) {
            const json &jGameObjects = layer["gameobject"];
            for (const auto &go : jGameObjects)
            {
                std::string goName = go["name"].get<std::string>();
                printf("Creating game object: %s\n", goName.c_str());
                int goX = go["x"].get<int>();
                int goY = go["y"].get<int>() - 5;
                auto obj = factory.create(goName,Vector2(goX,goY),textureManager);

                if(goName == "player") {
                    level->setCameraTarget(obj);
                    level->m_player = obj;
                } else {
                    level->addGameObject(obj);
                }
                // if(goName == cameraTarget){
                //     level->gameObject = obj.get();
                // }
                //obj->SetWorld(world);
                
                //gameObjects.emplace_back(std::move(obj));
                
            }
        }
        level->m_mainTilemap = tilemap;

        //world->AddLayer(layerName,std::make_unique<Layer>(std::move(tilemap),gameObjects));
    }

    return level;
}