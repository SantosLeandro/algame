#pragma once

#include "core/algame.hpp"
#include "core/vector2.hpp"
#include "game/tilemap.hpp"
#include "game/gameobject.hpp"
#include "game/player.hpp"
#include "game/gui.hpp"


class Game: public ALGame
{
public:
    Game();
    ~Game();
    int initialize() override;
    void update() override;
    void render() override;
    Tilemap *tileMap = nullptr;
    Player player;
    DialogBox *dialogBox;
    Button *button;
    std::string text;
    ALLEGRO_TRANSFORM transform;
   
    
};