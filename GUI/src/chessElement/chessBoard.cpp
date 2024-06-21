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
        throw NoParentWindow();
    }
    this->_ParentWindow = parentWindow;
    this->_SceneManager = parentWindow->getSceneManager();
    this->_Driver = parentWindow->getDriver();
    _WhiteTexture = parentWindow->getTextureLoader()->loadTexture("./GUI/assets/White.png");
    _BlackTexture = parentWindow->getTextureLoader()->loadTexture("./GUI/assets/Black.png");
    if (!_WhiteTexture || !_BlackTexture) {
        throw CouldNotLoadTexture();
    }
}

void chessBoard::setTileSize(float tileSize)
{
    if (tileSize <= 0) {
        throw InvalidTileSize();
    }
    _TileSize = tileSize;
}

void chessBoard::setWidth(int width)
{
    if (width <= 0) {
        throw InvalidWidth();
    }
    _Width = width;
}

void chessBoard::setHeight(int height)
{
    if (height <= 0) {
        throw InvalidHeight();
    }
    _Height = height;
}

void chessBoard::createBoard()
{
    int x;
    int y;

    if (_SceneManager == nullptr) {
        throw NoSceneManager();
    }
    if (_WhiteTexture == nullptr || _BlackTexture == nullptr) {
        throw NoTexturesSet();
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

void chessBoard::InitMap(int width, int height)
{
    for (int i = 0; i < width; i++) {
        std::vector<Tile *> tmp;
        for (int j = 0; j < height; j++) {
            tmp.push_back(new Tile());
        }
        _map.push_back(tmp);
    }
}

static std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void chessBoard::updateMapBtc(std::string response)
{
    std::vector<std::string> lines = split(response, ' ');

    int x = std::stoi(lines[1]);
    int y = std::stoi(lines[2]);
    int food = std::stoi(lines[3]);
    int linemate = std::stoi(lines[4]);
    int deraumere = std::stoi(lines[5]);
    int sibur = std::stoi(lines[6]);
    int mendiane = std::stoi(lines[7]);
    int phiras = std::stoi(lines[8]);
    int thystame = std::stoi(lines[9]);
    _map[x][y]->setInventory(food, linemate, deraumere, sibur, mendiane, phiras, thystame);
}

void chessBoard::printMap()
{
    for (int i = 0; i < _Width; i++) {
        for (int j = 0; j < _Height; j++) {
            _map[i][j]->printInventory();
        }
        std::cout << std::endl;
    }
}

void chessBoard::printMapAtPos(int x, int y)
{
    _map[x][y]->printInventory();
}
