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
    //m_camera = Camera(m_player, graphics.getVirualResolutionWidth(), graphics.getVirualResolutionHeight());
    m_camera.setTarget(m_player);
    m_camera.setWidth(graphics.getVirualResolutionWidth());
    m_camera.setHeight(graphics.getVirualResolutionHeight());
    m_camera.setMaxWidth(m_mainTilemap->getMapWidth() * m_mainTilemap->getTileWidth());
    m_camera.setMaxHeight(m_mainTilemap->getMapHeight() * m_mainTilemap->getTileHeight());
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
        if(checkCollision(*go, *m_player)){
            go->onCollision(m_player);
            m_player->onCollision(go);
        }
        // for(auto &other: m_gameObjects){
        //     if(go != other && checkCollision(*go, *other)){
        //         go->onCollision(other);
        //         other->onCollision(go);
        //     }
        // }
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
    if(m_transitioning && m_elapsed > 0) {
        m_elapsed -= 0.016f; // Assuming 60 FPS, adjust as needed
        graphics.drawRectangle(0,0, graphics.getVirualResolutionWidth(), graphics.getVirualResolutionHeight(), Color{0.0f, 0.0f, 0.0f, m_elapsed});
    } else {
        m_transitioning = false;
        m_elapsed = 1.0f;
    }
    m_player->render(graphics);
}

void Level::addGameObject(GameObject *go)
{
    m_gameObjects.push_back(go);
}

void Level::setCameraTarget(GameObject *target)
{
    m_camera.setTarget(target);
}

bool Level::checkCollision(GameObject &a, GameObject &b)
{
    auto boxA = a.getBoundingBox();
    auto boxB = b.getBoundingBox();

    auto posA = a.getPosition();
    auto posB = b.getPosition();

    float ax = posA.x + boxA.x;
    float ay = posA.y + boxA.y;
    float aw = boxA.w;
    float ah = boxA.h;

    float bx = posB.x + boxB.x;
    float by = posB.y + boxB.y;
    float bw = boxB.w;
    float bh = boxB.h;

    return (ax < bx + bw &&
            ax + aw > bx &&
            ay < by + bh &&
            ay + ah > by);
}

void Level::fadeIn()
{
    m_elapsed = 1.0f;
    m_transitioning = true;
    fadeInPosition = m_camera.getPosition();
}
