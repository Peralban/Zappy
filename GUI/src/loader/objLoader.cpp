/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** objLoader
*/

#include "loader/objLoader.hpp"

ObjLoader::ObjLoader()
{
}

ObjLoader::ObjLoader(irr::scene::ISceneManager *sceneManager)
{
    if (!sceneManager) {
        throw NoSceneManager();
    }
    _SceneManager = sceneManager;
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::setSceneManager(irr::scene::ISceneManager *sceneManager)
{
    if (!sceneManager) {
        throw NoSceneManager();
    }
    _SceneManager = sceneManager;
}

irr::scene::IAnimatedMesh *ObjLoader::loadObj(const char *path)
{
    irr::scene::IAnimatedMesh *mesh;

    if (!_SceneManager) {
        throw NoSceneManager();
    }
    mesh = _SceneManager->getMesh(path);
    if (!mesh) {
        throw UnableLoadObj();
    }
    return mesh;
}
