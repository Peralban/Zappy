/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** objLoader
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include <iostream>

class ObjLoader {
    public:
        ObjLoader();
        ObjLoader(irr::scene::ISceneManager *sceneManager);
        ~ObjLoader();

        void setSceneManager(irr::scene::ISceneManager *sceneManager);
    
        irr::scene::IAnimatedMesh* loadObj(const char *path);

    private:
        irr::scene::ISceneManager *_SceneManager;
};