#pragma once

#include "level.hpp"
#include "../core/graphics.hpp"
#include "maploader.hpp"
class LevelManager
{
public:
   
    void loadLevel(const char* filename, Graphics& graphics, TextureManager &textureManager, GameObjectFactory &factory);
    void unloadLevel(const char* filename);
    void releaseAllLevels();
    void changeCurrentLevel(const char* filename);
    Level* getCurrentLevel() { return m_currentLevel; }
    static LevelManager& getInstance();
private:
    Level* m_currentLevel;
    std::map<std::string, Level*> m_levels;
    MapLoader m_mapLoader;
     LevelManager();
    ~LevelManager();
};