#pragma once

#include <string>
#include <unordered_map>

#include "texture.hpp"
#include <memory>

class TextureManager
{
    protected:
        std::unordered_map<std::string, std::unique_ptr<Texture>> m_texturemap;
    public:
        TextureManager();
        void release();
        bool load(const std::string &filename);
        void generateMask(const std::string &filename);
        Texture* get(const std::string& id);
};