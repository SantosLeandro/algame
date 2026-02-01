#include "texture.hpp"

Texture::Texture()
    : m_bitmap(nullptr)
    , m_width(0)
    , m_height(0)
{
}

Texture::~Texture()
{
    if(m_bitmap)
        al_destroy_bitmap(m_bitmap);
}

bool Texture::loadFromFile(const char *filename)
{
    m_bitmap = al_load_bitmap(filename);
    if(!m_bitmap)
    {
        printf("failed to load bitmap from file: %s\n", filename);
        return false;
    } else {
        printf("bitmap loaded from file: %s\n", filename);
    }
    m_width = al_get_bitmap_width(m_bitmap);
    m_height = al_get_bitmap_height(m_bitmap);
    return true;
}

int Texture::getWidth() const
{
    return m_width;
}

int Texture::getHeight() const
{
    return m_height;
}
