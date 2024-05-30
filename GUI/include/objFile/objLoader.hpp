/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** objLoader
*/

#pragma once

#include "main.hpp"

class objLoader {
    public:
        objLoader(ISceneManager *smgr, IVideoDriver *driver);
        ~objLoader();
        void loadObj(const char *path);
    private:
        ISceneManager* smgr;
        IVideoDriver* driver;
        IAnimatedMesh* mesh;
};
