#include "graphics.hpp"
#include "texture.hpp"
#include <stdio.h>

Graphics::Graphics() : m_font(nullptr), m_display(nullptr), m_virtualBitmap(nullptr), m_virtualWidth(0), m_virtualHeight(0)
{
}

Graphics::~Graphics()
{
    if (m_virtualBitmap)
        al_destroy_bitmap(m_virtualBitmap);
    if (m_font)
        al_destroy_font(m_font);
}

void Graphics::initialize(ALLEGRO_DISPLAY *display)
{
    m_display = display;
    m_font = al_create_builtin_font();
    if (!m_font)
    {
        printf("couldn't initialize font\n");
        return;
    }
}

void Graphics::setResolution(int width, int height)
{
    al_resize_display(m_display, width, height);
}

void Graphics::clear()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Graphics::present()
{
    al_flip_display();
    if(!m_virtualBitmap)
        return;
    al_set_target_backbuffer(m_display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(m_virtualBitmap,
                          0, 0, m_virtualWidth, m_virtualHeight,
                          0, 0, al_get_display_width(m_display),  al_get_display_height(m_display), 0);
    al_flip_display();
    al_set_target_bitmap(m_virtualBitmap);
}

void Graphics::drawText(const char *text, int x, int y)
{
    al_draw_text(m_font, al_map_rgb(255, 255, 255), x, y, 0, text);
}

void Graphics::drawRectangle(int x, int y, int w, int h)
{
    al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
}

void Graphics::drawRectangle(int x, int y, int w, int h, const Color &color)
{
    al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgba_f(color.r, color.g, color.b, color.a));
}

void Graphics::drawTexture(Texture *texture, int x, int y)
{
    al_draw_bitmap(texture->getBitmap(), x, y, 0);
}

void Graphics::drawTextureRegion(Texture *texture, int sx, int sy, int sw, int sh, int dx, int dy, int flip)
{
    al_draw_bitmap_region(texture->getBitmap(), sx, sy, sw, sh, dx, dy, flip);
}

void Graphics::setVirtualResolution(int width, int height)
{
    m_virtualWidth = width;
    m_virtualHeight = height;
    // if (m_virtualBitmap)
    //     al_destroy_bitmap(m_virtualBitmap);
    m_virtualBitmap = al_create_bitmap(width, height);
    al_set_target_bitmap(m_virtualBitmap);
}
