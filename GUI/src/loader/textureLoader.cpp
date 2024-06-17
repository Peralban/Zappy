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
    if (!driver) {
        std::cerr << "TextureLoader: Error: No video driver set for texture loader." << std::endl;
        exit(EXIT_FAILURE);
    }
    _Driver = driver;
}


TextureLoader::~TextureLoader()
{
}

void TextureLoader::setDriver(irr::video::IVideoDriver *driver)
{
    if (!driver) {
        std::cerr << "TextureLoader: Error: No video driver set for texture loader." << std::endl;
        exit(EXIT_FAILURE);
    }
    _Driver = driver;
}

irr::video::ITexture *TextureLoader::loadTexture(const char *path)
{
    irr::video::ITexture *texture;

    if (!_Driver) {
        std::cerr << "loadTexture: Error: No video driver set for texture loader." << std::endl;
        exit(EXIT_FAILURE);
    }
    texture = _Driver->getTexture(path);
    if (!texture) {
        std::cerr << "loadTexture: Error: Could not load texture: " << path << std::endl;
        exit(EXIT_FAILURE);
    }
    return texture;
}
