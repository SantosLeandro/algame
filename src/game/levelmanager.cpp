#include "levelmanager.hpp"

LevelManager::LevelManager() : m_currentLevel(nullptr)
{
}
LevelManager& LevelManager::getInstance()
{
    static LevelManager instance;
    return instance;
}

void LevelManager::loadLevel(const char *filename, Graphics &graphics, TextureManager &textureManager, GameObjectFactory &factory)
{
    m_currentLevel = m_mapLoader.load(filename, graphics, textureManager, factory);
    m_currentLevel->initialize(graphics);
    m_levels[filename] = m_currentLevel;

}

void LevelManager::unloadLevel(const char *filename)
{
    auto it = m_levels.find(filename);
    if (it != m_levels.end()) {
        delete it->second;
        m_levels.erase(it);
    }
}

void LevelManager::releaseAllLevels()
{
    for (auto &pair : m_levels) {
        delete pair.second;
    }
    m_levels.clear();
}

void LevelManager::changeCurrentLevel(const char *filename)
{
    auto it = m_levels.find(filename);
    if (it != m_levels.end()) {
        m_currentLevel = it->second;
    }
}

LevelManager::~LevelManager()
{
    for (auto &pair : m_levels) {
        delete pair.second;
    }
}
