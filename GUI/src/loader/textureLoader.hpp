/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** objLoader
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include <iostream>

class TextureLoader {
    public:
        TextureLoader();
        TextureLoader(irr::video::IVideoDriver *driver);
        ~TextureLoader();

        void setDriver(irr::video::IVideoDriver *driver);

        irr::video::ITexture* loadTexture(const char *path);
    private:
        irr::video::IVideoDriver *_Driver;
};
