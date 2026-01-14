#include "level.hpp"

Level::Level()
{

}

Level::Level(GameObject *player, Tilemap *mainTilemap)
{
    m_player = player;
    m_mainTilemap = mainTilemap;
}

void Level::initialize(Graphics &graphics)
{
    m_camera = Camera(m_player, graphics.getVirualResolutionWidth(), graphics.getVirualResolutionHeight());
}

void Level::update()
{
    m_player->update();
    m_mainTilemap->processCollision(*m_player);
    m_player->setPosition(Vector2(
        m_player->getPosition().x + m_player->getVelocity().x,
        m_player->getPosition().y + m_player->getVelocity().y
    ));
    for(auto &go: m_gameObjects){
        go->update();
        m_mainTilemap->processCollision(*go);
        go->setPosition({
            go->getPosition().x + go->getVelocity().x,
            go->getPosition().y + go->getVelocity().y
        });
    }

}

void Level::render(Graphics &graphics)
{
    m_camera.update();
    m_mainTilemap->render(graphics,0,0);
    for(auto &go: m_gameObjects){
        go->render(graphics);
    }
    m_player->render(graphics);
}

void Level::addGameObject(GameObject *go)
{
    m_gameObjects.push_back(go);
}
