#pragma once

#include "../core/vector2.hpp"

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
protected:
    Vector2 position;
    Vector2 velocity;
    Texture* texture;
    Box boundingBox;
    bool onGround = false;

};   