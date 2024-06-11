/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** TextureLoader
*/

#include "loader/textureLoader.hpp"

TextureLoader::TextureLoader()
{
}

TextureLoader::TextureLoader(irr::video::IVideoDriver *driver)
{
    _Driver = driver;
}


TextureLoader::~TextureLoader()
{
}

void TextureLoader::setDriver(irr::video::IVideoDriver *driver)
{
    _Driver = driver;
}

irr::video::ITexture *TextureLoader::loadTexture(const char *path)
{
    irr::video::ITexture *texture;

    if (!_Driver)
        return nullptr;
    texture = _Driver->getTexture(path);
    if (!texture) {
        std::cerr << "Error: Could not load texture: " << path << std::endl;
        exit(84);
    }
    return texture;
}
