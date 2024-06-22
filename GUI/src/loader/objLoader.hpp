/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** objLoader
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include <iostream>
#include "../interface/AError.hpp"

/**
 * @class ObjLoader
 * @brief The ObjLoader class is responsible for loading OBJ files and then creating animated meshes in the Irrlicht scene.
 */
class ObjLoader {
    public:
        /**
         * @brief Default constructor for the ObjLoader class.
         */
        ObjLoader();

        /**
         * @brief Constructor for the ObjLoader class that takes an Irrlicht scene manager as a parameter.
         * @param sceneManager The Irrlicht scene manager used to create the animated meshes.
         */
        ObjLoader(irr::scene::ISceneManager *sceneManager);

        /**
         * @brief Destructor for the ObjLoader class.
         */
        ~ObjLoader();

        /**
         * @brief Sets the Irrlicht scene manager used to create the animated meshes.
         * @param sceneManager The Irrlicht scene manager.
         */
        void setSceneManager(irr::scene::ISceneManager *sceneManager);
    
        /**
         * @brief Loads an OBJ file and creates an animated mesh.
         * @param path The path to the OBJ file.
         * @return The loaded animated mesh.
         */
        irr::scene::IAnimatedMesh* loadObj(const char *path);

        class NoSceneManager : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "No scene manager set for obj loader.".
             */
            NoSceneManager() : AError("No scene manager set for obj loader.") {}
        };

        class UnableLoadObj : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Could not load obj.".
             */
            UnableLoadObj() : AError("Could not load obj.") {}
        };

    private:
        irr::scene::ISceneManager *_SceneManager; /**< The Irrlicht scene manager used to create the animated meshes. */
};
