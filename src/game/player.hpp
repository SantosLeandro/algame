#pragma once

#include "../core/graphics.hpp"
#include "../core/vector2.hpp"
#include "gameobject.hpp"
#include "animation.hpp"
#include <array>
#include <vector>

class Player : public GameObject
{
public:
    Player();
    Player(const Vector2 &pos, Texture *tex);
    ~Player();
    void update() override;
    void render(Graphics &graphics) override;
    AnimationController animationController;
private:
    float speed = 2.0f;
    int flipState = 0;
};