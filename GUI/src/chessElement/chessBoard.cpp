/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#include "chessElement/chessBoard.hpp"

chessBoard::chessBoard()
{
    this->sceneManager = nullptr;
    this->driver = nullptr;
    this->width = 0;
    this->height = 0;
    this->tileSize = 0;
}

chessBoard::chessBoard(scene::ISceneManager *smgr, video::IVideoDriver *driver, int width, int height, float tileSize)
{
    this->sceneManager = smgr;
    this->driver = driver;
    this->width = width;
    this->height = height;
    this->tileSize = tileSize;	
}

chessBoard::~chessBoard()
{
}

void chessBoard::createBoard()
{
    whiteTexture = driver->getTexture("./assets/White.png");
    blackTexture = driver->getTexture("./assets/Black.png");
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
			ITexture* tileTexture = ((x + y) % 2 == 0) ? whiteTexture : blackTexture;
			scene::ISceneNode* tile = const_cast<scene::ISceneManager*>(sceneManager)->addCubeSceneNode(tileSize);
            if (tile) {
                tile->setPosition(irr::core::vector3df(x * tileSize, 0, y * tileSize));
                tile->setMaterialFlag(video::EMF_LIGHTING, false);
                tile->setMaterialTexture(0, tileTexture);
                tile->setMaterialType(video::EMT_SOLID);
                tile->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);
            }
        }
    }
}
