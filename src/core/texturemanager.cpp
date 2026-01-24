#include "texturemanager.hpp"
#include <iostream>
#include <string>

TextureManager::TextureManager()
{
}

bool TextureManager::load(const std::string &filename)
{
    std::unique_ptr<Texture> tex = std::make_unique<Texture>();
    if (!tex->loadFromFile(filename.c_str())) {
        std::cerr << "Falha ao carregar textura: " << filename << "\n";
        return false;
    }
    
    m_texturemap[filename] = std::move(tex);
    return true;
}

void TextureManager::generateMask(const std::string &filename)
{
    //m_texturemap[filename].get()->CreateMask();
}

Texture* TextureManager::get(const std::string& id) {
    auto it = m_texturemap.find(id);
    if (it != m_texturemap.end()) {
        return it->second.get();
    }
    return nullptr;
}

void TextureManager::release() {
    m_texturemap.clear();
}