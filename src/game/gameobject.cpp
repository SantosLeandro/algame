#include "gameobject.hpp"
#include "../core/graphics.hpp"
#include "../core/input.hpp"
#include "../core/joystick.hpp"

GameObject::GameObject()
{
}

GameObject::GameObject(const Vector2 &pos, Texture *tex)
{
    position = pos;
    texture = tex;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
    // boundingBox.x = static_cast<int>(position.x);
    // boundingBox.y = static_cast<int>(position.y);
}

void GameObject::render(Graphics &graphics)
{
    graphics.drawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y));
}
