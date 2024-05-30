/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** objLoader
*/

#include "objFile/objLoader.hpp"

objLoader::objLoader(ISceneManager* smgr, IVideoDriver* driver)
{
    this->smgr = smgr;
    this->driver = driver;
}

objLoader::~objLoader()
{
}

void objLoader::loadObj(const char* path)
{
}