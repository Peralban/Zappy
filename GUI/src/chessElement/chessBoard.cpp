/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#include "chessBoard.hpp"
#include <iostream>

chessBoard::chessBoard(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, int width, int height, float tileSize)
{
    this->_SceneManager = smgr;
    this->_Driver = driver;
    this->_Width = width;
    this->_Height = height;
    this->_TileSize = tileSize;	
    _WhiteTexture = driver->getTexture("./GUI/assets/White.png");
    _BlackTexture = driver->getTexture("./GUI/assets/Black.png");
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
