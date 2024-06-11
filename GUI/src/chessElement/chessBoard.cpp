/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#include "chessBoard.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

chessBoard::chessBoard(irrlichtWindow *parentWindow, int width, int height, float tileSize)
{
    this->_ParentWindow = parentWindow;
    this->_SceneManager = parentWindow->getSceneManager();
    this->_Driver = parentWindow->getDriver();
    this->_Width = width;
    this->_Height = height;
    this->_TileSize = tileSize;	
    _WhiteTexture = parentWindow->getTextureLoader()->loadTexture("./GUI/assets/White.png");
    _BlackTexture = parentWindow->getTextureLoader()->loadTexture("./GUI/assets/Black.png");
    if (!_WhiteTexture || !_BlackTexture) {
        std::cerr << "Error: Could not load textures" << std::endl;
        exit(84);
    }
}

chessBoard::~chessBoard()
{
}

void chessBoard::createBoard()
{
    for (int x = 0; x < _Width; ++x) {
        for (int y = 0; y < _Height; ++y) {
			irr::video::ITexture* _TileTexture = ((x + y) % 2 == 0) ? _WhiteTexture : _BlackTexture;
			irr::scene::ISceneNode* tile = const_cast<irr::scene::ISceneManager*>(_SceneManager)->addCubeSceneNode(_TileSize);
            if (tile) {
                tile->setPosition(irr::core::vector3df(x * _TileSize, 0, y * _TileSize));
                tile->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                tile->setMaterialTexture(0, _TileTexture);
                tile->setMaterialType(irr::video::EMT_SOLID);
                tile->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
            }
        }
    }
}
