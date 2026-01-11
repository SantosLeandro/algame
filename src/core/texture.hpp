#pragma once

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

class Texture {
public:
    Texture();
    ~Texture();
    bool loadFromFile(const char* filename);
    int getWidth() const;
    int getHeight() const;
    ALLEGRO_BITMAP* getBitmap() const { return m_bitmap; }
    void* getBitmapPtr() { return m_bitmap; }
private:
    ALLEGRO_BITMAP* m_bitmap;
    int m_width;
    int m_height;
};