/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** objLoader
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "../interface/AError.hpp"
#include <iostream>
#include <map>

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
         * @brief Adds a texture with the specified RGBA values.
         * @param Red The red value of the texture.
         * @param Green The green value of the texture.
         * @param Blue The blue value of the texture.
         * @param Alpha The alpha value of the texture.
         * @param name The name of the texture.
         */
        void addTexture(int Red, int Green, int Blue, int Alpha = 255, std::string name = "default");

        /**
         * @brief Removes the texture with the specified name.
         * @param name The name of the texture to be removed.
         */
        void removeTexture(std::string name);

        /**
         * @brief Loads a texture from the specified file path.
         * @param path The file path of the texture to be loaded.
         * @return The loaded texture as an Irrlicht video texture.
         */
        irr::video::ITexture* loadTexture(const char *path);

        /**
         * @brief Creates a texture with the specified RGBA values.
         * @param Red The red value of the texture.
         * @param Green The green value of the texture.
         * @param Blue The blue value of the texture.
         * @param Alpha The alpha value of the texture.
         * @return The created texture as an Irrlicht video texture.
         */
        irr::video::ITexture* createTexture(int Red, int Green, int Blue, int Alpha = 255);

        /**
         * @brief Creates a texture with the specified RGBA values and name.
         * @param Red The red value of the texture.
         * @param Green The green value of the texture.
         * @param Blue The blue value of the texture.
         * @param Alpha The alpha value of the texture.
         * @param name The name of the texture.
         * @return The created texture as an Irrlicht video texture.
         */
        irr::video::ITexture* createGetTexture(int Red, int Green, int Blue, int Alpha = 255, std::string name = "default");

        /**
         * @brief Gets the texture with the specified name.
         * @param name The name of the texture to be retrieved.
         * @return The texture with the specified name as an Irrlicht video texture.
         */
        irr::video::ITexture* getTexture(std::string name);
        
        class NoVideoDriver : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "No video driver set for texture loader".
             */
            NoVideoDriver() : AError("No video driver set for texture loader.") {}
        };

        class NotFindTexture : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Could not find texture.".
             */
            NotFindTexture() : AError("Could not find texture.") {}
        };

    private:
        irr::video::IVideoDriver *_Driver; /**< The Irrlicht video driver used for loading textures. */
        std::map<std::string, irr::video::ITexture*> _Textures; /**< A map of texture names to texture objects. */
};
