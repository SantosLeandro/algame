#pragma once

#include "core/algame.hpp"
#include "core/vector2.hpp"
#include "game/tilemap.hpp"
#include "game/gameobject.hpp"
#include "game/player.hpp"
#include "game/gui.hpp"
#include "game/level.hpp"
#include "game/objectfactory.hpp"
#include "core/texturemanager.hpp"


class Game: public ALGame
{
public:
    Game();
    ~Game();
    void initialize() override;
    void update() override;
    void render() override;
    Tilemap *tileMap = nullptr;
    Player player;
    DialogBox *dialogBox;
    Button *button;
    std::string text;
    Level *level;
    Camera guiCamera;
    TextureManager m_textureManager;
};