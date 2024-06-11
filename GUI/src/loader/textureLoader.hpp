/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** objLoader
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include <iostream>

/**
 * @class TextureLoader
 * @brief The TextureLoader class is responsible for loading textures using the Irrlicht video driver.
 */
class TextureLoader {
    public:
        /**
         * @brief Default constructor for TextureLoader.
         */
        TextureLoader();

        /**
         * @brief Constructor for TextureLoader that takes an Irrlicht video driver as a parameter.
         * @param driver The Irrlicht video driver to be used for loading textures.
         */
        TextureLoader(irr::video::IVideoDriver *driver);

        /**
         * @brief Destructor for TextureLoader.
         */
        ~TextureLoader();

        /**
         * @brief Sets the Irrlicht video driver to be used for loading textures.
         * @param driver The Irrlicht video driver to be set.
         */
        void setDriver(irr::video::IVideoDriver *driver);

        /**
         * @brief Loads a texture from the specified file path.
         * @param path The file path of the texture to be loaded.
         * @return The loaded texture as an Irrlicht video texture.
         */
        irr::video::ITexture* loadTexture(const char *path);

    private:
        irr::video::IVideoDriver *_Driver; /**< The Irrlicht video driver used for loading textures. */
};
