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
        std::cerr << "ObjLoader: Error: No scene manager set for obj loader." << std::endl;
        exit(EXIT_FAILURE);
    }
    _SceneManager = sceneManager;
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::setSceneManager(irr::scene::ISceneManager *sceneManager)
{
    if (!sceneManager) {
        std::cerr << "ObjLoader: Error: No scene manager set for obj loader." << std::endl;
        exit(EXIT_FAILURE);
    }
    _SceneManager = sceneManager;
}

irr::scene::IAnimatedMesh *ObjLoader::loadObj(const char *path)
{
    irr::scene::IAnimatedMesh *mesh;

    if (!_SceneManager) {
        std::cerr << "Error: No scene manager set for obj loader." << std::endl;
        exit(EXIT_FAILURE);
    }
    mesh = _SceneManager->getMesh(path);
    if (!mesh) {
        std::cerr << "Error: Could not load obj: " << path << std::endl;
        exit(EXIT_FAILURE);
    }
    return mesh;
}
