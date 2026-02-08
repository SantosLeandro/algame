#include "door.hpp"
#include "../core/graphics.hpp"

Door::Door()
{
}

Door::Door(const Vector2 &pos, Texture *tex) : GameObject(pos, tex)
{
    name = "door";
    boundingBox.w = 16;
    boundingBox.h = 64;
    boundingBox.x = 0;
    boundingBox.y = 0;
}

Door::~Door()
{
}

void Door::render(Graphics &graphics)
{
    graphics.drawTextureRegion(texture, 188, 262, 16, 64, static_cast<int>(position.x), static_cast<int>(position.y),0);
}
