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
    // if(m_transitioning && elapsed < duration) {
    //     elapsed += 16; // Assuming 60 FPS, adjust as needed
        
    // } else {
        
    //     m_transitioning = false;
    //     elapsed = 0;
       
    // }
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

void Level::transition()
{
    m_transitioning = true;
}
