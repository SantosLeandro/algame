#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
//#include "layer.hpp"
#include "level.hpp"
#include "../core/texturemanager.hpp"
#include "objectfactory.hpp"

using json = nlohmann::json;

class MapLoader
{
private:
    /* data */
public:
    MapLoader(/* args */);
    ~MapLoader();
    Level* load(const char* filename, Graphics& graphics, TextureManager &textureManager, GameObjectFactory &factory);


};

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
        return level;
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
    const json &jLayers = root["layer"];
    for (const auto &layer : jLayers)
    {
        std::string textureFilename = layer["texture"].get<std::string>();
        auto texture = textureManager.get("content//"+textureFilename);
        if(texture == nullptr) {
            textureManager.load(textureFilename);
            texture = textureManager.get(textureFilename);
        }
        

        int width = layer["width"].get<int>();
        int height = layer["height"].get<int>();
        std::string layerName = layer["name"].get<std::string>();

        std::string eData = layer["data"].get<std::string>();
        std::stringstream ss(eData);
        std::string token;
        std::vector<std::string> temp;

        std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>();
        tilemap->setTexture(texture);
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
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        
        if(layer.contains("gameobject")) {
            const json &jGameObjects = layer["gameobject"];
            for (const auto &go : jGameObjects)
            {
                std::string goName = go["name"].get<std::string>();
                int goX = go["x"].get<int>();
                int goY = go["y"].get<int>();
                auto obj = factory.create(goName,Vector2(goX,goY),textureManager);
                // if(goName == cameraTarget){
                //     level->gameObject = obj.get();
                // }
                //obj->SetWorld(world);
                level->addGameObject(std::move(obj));
                //gameObjects.emplace_back(std::move(obj));
                
            }
        }

        //world->AddLayer(layerName,std::make_unique<Layer>(std::move(tilemap),gameObjects));
    }

    return level;
}