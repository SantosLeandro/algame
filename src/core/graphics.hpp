#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


struct Color
{
    float r;
    float g;
    float b;
    float a;
};


class Texture;

class Graphics {
public:
    Graphics();
    ~Graphics();
    void initialize(ALLEGRO_DISPLAY* display);
    void setResolution(int width, int height);
    void clear();
    void present();
    void drawText(const char* text, int x, int y);
    void drawRectangle(int x, int y, int w, int h);
    void drawRectangle(int x, int y, int w, int h, const Color &color);
    void drawTexture(Texture *texture, int x, int y);
    void drawTextureRegion(Texture *texture, int sx, int sy, int sw, int sh, int dx, int dy,int flip);
    void setVirtualResolution(int width, int height);
    int getVirualResolutionWidth();
    int getVirualResolutionHeight();
private:
    ALLEGRO_FONT* m_font;
    ALLEGRO_DISPLAY* m_display;
    ALLEGRO_BITMAP* m_virtualBitmap;
    int m_virtualWidth;
    int m_virtualHeight;
};