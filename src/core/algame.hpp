#pragma once

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "graphics.hpp"
#include "texture.hpp"
#include "input.hpp"
#include "key.hpp"
#include "joystick.hpp"

class ALGame
{
public:
    ALGame();
    ~ALGame();
    void run();
    virtual int initialize();
    virtual void update();
    virtual void render();
protected:
    ALLEGRO_TIMER* m_timer;
    ALLEGRO_EVENT_QUEUE* m_queue;
    ALLEGRO_DISPLAY* m_disp;
    ALLEGRO_FONT* m_font;
    Graphics m_graphics;
    Texture m_texture;
    unsigned char m_key[ALLEGRO_KEY_MAX];
private:
    const int KEY_SEEN = 1;
    const int KEY_DOWN = 2;
    void must_init(bool test, const char *description);
    void process_input();
    bool m_running;
};