#pragma once

#include <allegro5/allegro.h>
#include "gameobject.hpp"
#include "../core/vector2.hpp"


class Camera
{
    public:
        Camera();
        Camera(GameObject *target, int w, int h);
        void setTarget(GameObject *target);
        void setWidth(int w) { m_w = w; }
        void setHeight(int h) { m_h = h; }
        void setMaxWidth(int w);
        void setMaxHeight(int h);
        void setOffset(const Vector2& offset) { m_offset = offset; }
        void update();
    protected:
        ALLEGRO_TRANSFORM m_transform;
        GameObject *m_target;
        Vector2 m_offset;
        int m_w;
        int m_h;
        int m_maxW;
        int m_maxH;
        Vector2 m_position;
        float m_smooth;
        


};