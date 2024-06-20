/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#include "chessBoard.hpp"
#include "../game/ZappyGame.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

chessBoard::chessBoard(ZappyGame *ParentZappy, int width, int height, float tileSize)
{
    setParentWindow(ParentZappy->getParentDevice());
    if (width == -1)
        width = ParentZappy->getPlatformWidth();
    if (height == -1)
        height = ParentZappy->getPlatformHeight();
    if (tileSize == -1)
        tileSize = ParentZappy->getTileSize();
    setTileSize(tileSize);
    setWidth(width);
    setHeight(height);
}

chessBoard::chessBoard()
{
}

chessBoard::~chessBoard()
{
    this->_BlackTexture->drop();
    this->_WhiteTexture->drop();
}

void chessBoard::setParentWindow(irrlichtWindow *parentWindow)
{
   if (parentWindow == nullptr) {
        std::cerr << "chessBoard: Error: No parent window set." << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_ParentWindow = parentWindow;
    this->_SceneManager = parentWindow->getSceneManager();
    this->_Driver = parentWindow->getDriver();
    _WhiteTexture = parentWindow->getTextureLoader()->loadTexture("./GUI/assets/White.png");
    _BlackTexture = parentWindow->getTextureLoader()->loadTexture("./GUI/assets/Black.png");
    if (!_WhiteTexture || !_BlackTexture) {
        std::cerr << "chessBoard: Error: Could not load textures" << std::endl;
        exit(84);
    }
}

void chessBoard::setTileSize(float tileSize)
{
    if (tileSize <= 0) {
        std::cerr << "setTileSize: Error: Invalid tile size for chess board." << std::endl;
        exit(EXIT_FAILURE);
    }
    _TileSize = tileSize;
}

void chessBoard::setWidth(int width)
{
    if (width <= 0) {
        std::cerr << "setWidth: Error: Invalid width for chess board." << std::endl;
        exit(EXIT_FAILURE);
    }
    _Width = width;
}

void chessBoard::setHeight(int height)
{
    if (height <= 0) {
        std::cerr << "setHeight: Error: Invalid height for chess board." << std::endl;
        exit(EXIT_FAILURE);
    }
    _Height = height;
}

void chessBoard::createBoard()
{
    int x;
    int y;

    if (_SceneManager == nullptr) {
        std::cerr << "createBoard: Error: No scene manager set for chess board." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (_WhiteTexture == nullptr || _BlackTexture == nullptr) {
        std::cerr << "createBoard: Error: No textures set for chess board." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (x = 0; x < _Width; ++x) {
        for (y = 0; y < _Height; ++y) {
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
    _IsCreated = true;
}

bool chessBoard::isCreated()
{
    return _IsCreated;
}
