#pragma once

#include <memory>
#include "../core/texturemanager.hpp"
#include "gameobject.hpp"
#include "player.hpp"
#include "door.hpp"

class GameObjectFactory
{
public:
    GameObject* create(const std::string &name, const Vector2 &position, TextureManager &textureManeger)
    {
        if (name == "player") {
            Texture* tex = textureManeger.get("texture//samus.png");
            return new Player(position, tex);
        } else if(name == "enemy1"){
            Texture* tex = textureManeger.get("texture//samus.png");
            return new Enemy(position, tex);
        } else if(name == "door"){
            Texture* tex = textureManeger.get("texture//samus.png");
            return new Door(position, tex);
        }
        return new GameObject(position, textureManeger.get("texture//samus.png"));
    }
};