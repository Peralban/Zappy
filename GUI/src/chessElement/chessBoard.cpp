/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#include "chessElement/chessBoard.hpp"

chessBoard::chessBoard(scene::ISceneManager *smgr, video::IVideoDriver *driver, int width, int height, float tileSize)
{
    this->_SceneManager = smgr;
    this->_Driver = driver;
    this->_Width = width;
    this->_Height = height;
    this->_TileSize = tileSize;	
    _WhiteTexture = driver->getTexture("./assets/White.png");
    _BlackTexture = driver->getTexture("./assets/Black.png");
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
			ITexture* _TileTexture = ((x + y) % 2 == 0) ? _WhiteTexture : _BlackTexture;
			scene::ISceneNode* tile = const_cast<scene::ISceneManager*>(_SceneManager)->addCubeSceneNode(_TileSize);
            if (tile) {
                tile->setPosition(irr::core::vector3df(x * _TileSize, 0, y * _TileSize));
                tile->setMaterialFlag(video::EMF_LIGHTING, false);
                tile->setMaterialTexture(0, _TileTexture);
                tile->setMaterialType(video::EMT_SOLID);
                tile->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);
            }
        }
    }
}
