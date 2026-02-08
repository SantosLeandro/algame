#pragma once

#include "../core/vector2.hpp"
#include <string>
#include <unordered_map>

class Graphics;
class Texture;
class Vector2;

struct Box
{
    int x = 0;
    int y = 0;
    int w = 32;
    int h = 32;
};

class GameObject {
public:
    GameObject();
    GameObject(const Vector2& pos, Texture* tex);
    virtual ~GameObject();
    virtual void update();
    virtual void render(Graphics &graphics);
    virtual Vector2 getPosition() const { return position; }
    virtual void setPosition(const Vector2& pos) { position = pos; }
    Vector2 getVelocity() const { return velocity; }
    void setVelocity(const Vector2& vel) { velocity = vel; }
    void setVelocityX(float x) { velocity.x = x; }
    void setVelocityY(float y) { velocity.y = y; }    
    Box getBoundingBox() const { return boundingBox; }
    void setOnGround(bool val) { onGround = val; }
    bool isOnGround() const { return onGround; }
    virtual void onTileCollision(int tile , int signX, int signY){}
    void setTag(const std::string& t) { tag = t; }
    std::string getTag() const { return tag; }
    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }
    virtual void onCollision(GameObject* other){}
    void setAttribute(const std::string& key, const std::string& value) {
        m_attributes[key] = value;
    }
    std::string getAttribute(const std::string& key) const {
        auto it = m_attributes.find(key);
        if (it != m_attributes.end()) {
            return it->second;
        }
        return "";
    }
protected:
    std::unordered_map<std::string, std::string> m_attributes;
    std::string name;
    std::string tag;
    Vector2 position;
    Vector2 velocity;
    Texture* texture;
    Box boundingBox;
    bool onGround = false;

};   