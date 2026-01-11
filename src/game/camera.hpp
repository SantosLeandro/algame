#pragma once

#include <allegro5/allegro.h>
#include "gameobject.hpp"
#include "../core/vector2.hpp"


class Camera
{
    public:
        Camera();
        Camera(GameObject *target, int w, int h);
        void update();
    protected:
        ALLEGRO_TRANSFORM m_transform;
        GameObject *m_target;
        int m_w;
        int m_h;
        Vector2 m_position;
        float m_smooth;
        


};