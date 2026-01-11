#include "texture.hpp"

Texture::Texture()
{
}

Texture::~Texture()
{
    al_destroy_bitmap(m_bitmap);
}

bool Texture::loadFromFile(const char *filename)
{
    m_bitmap = al_load_bitmap(filename);
    if(!m_bitmap)
    {
        printf("failed to load bitmap from file: %s\n", filename);
        return false;
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
