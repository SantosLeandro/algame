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

