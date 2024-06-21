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
        throw NoVideoDriver();
    }
    _Driver = driver;
}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::setDriver(irr::video::IVideoDriver *driver)
{
    if (!driver) {
        throw NoVideoDriver();
    }
    _Driver = driver;
}

void TextureLoader::addTexture(int Red, int Green, int Blue, int Alpha, std::string name)
{
    irr::video::ITexture *texture = createTexture(Red, Green, Blue, Alpha);
    _Textures[name] = texture;
}

void TextureLoader::removeTexture(std::string name)
{
    _Textures.erase(name);
}

irr::video::ITexture *TextureLoader::loadTexture(const char *path)
{
    irr::video::ITexture *texture;

    if (!_Driver) {
        throw NoVideoDriver();
    }
    texture = _Driver->getTexture(path);
    if (!texture) {
        throw NotFindTexture();
    }
    return texture;
}

irr::video::ITexture *TextureLoader::createTexture(int Red, int Green, int Blue, int Alpha)
{
    irr::u32 width = 256;
    irr::u32 height = 256;
    irr::video::IImage *tmpImage;
    irr::video::ITexture *tmpTexture;
    std::string name = "Texture";
    irr::video::SColor color(Alpha, Red, Green, Blue);
    if (!_Driver) {
        throw NoVideoDriver();
    }
    tmpImage = _Driver->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(width, height));
    for (irr::u32 y = 0; y < height; ++y)
        for (irr::u32 x = 0; x < width; ++x)
            tmpImage->setPixel(x, y, color);
    name += std::to_string(Red) + std::to_string(Green) + std::to_string(Blue) + std::to_string(Alpha);
    tmpTexture = _Driver->addTexture(name.c_str(), tmpImage);
    tmpImage->drop();
    return tmpTexture;
}

irr::video::ITexture *TextureLoader::createGetTexture(int Red, int Green, int Blue, int Alpha, std::string name)
{
    if (_Textures.find(name) != _Textures.end()) {
        return _Textures[name];
    }
    irr::video::ITexture *texture = createTexture(Red, Green, Blue, Alpha);
    _Textures[name] = texture;
    return texture;
}

irr::video::ITexture *TextureLoader::getTexture(std::string name)
{
    if (_Textures.find(name) == _Textures.end()) {
        throw NotFindTexture();
    }
    return _Textures[name];
}
