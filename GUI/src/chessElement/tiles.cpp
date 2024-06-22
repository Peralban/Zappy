/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tiles
*/

#include "tiles.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"
#include "chessElement/chessBoard.hpp"
#include "items/items.hpp"

Tile::Tile()
{
    _food = 0;
    _linemate = 0;
    _deraumere = 0;
    _sibur = 0;
    _mendiane = 0;
    _phiras = 0;
    _thystame = 0;
    _player = 0;
    _egg = 0;
}

Tile::Tile(chessBoard *ParentChessBoard, irr::video::ITexture* tileTexture, int x, int y, int z, float tileSize)
{
    _food = 0;
    _linemate = 0;
    _deraumere = 0;
    _sibur = 0;
    _mendiane = 0;
    _phiras = 0;
    _thystame = 0;
    _player = 0;
    _egg = 0;
    _X = x;
    _Y = y;
    _Z = z;
    _TileSize = tileSize;
    if (ParentChessBoard == nullptr) {
        throw UnsetParentChessboard();
    }
    _ParentChessBoard = ParentChessBoard;
    if (tileTexture == nullptr) {
        throw UnsetTileTexture();
    }
    _TileTexture = tileTexture;
}

Tile::~Tile()
{
}

void Tile::linkToParent(chessBoard *ParentChessBoard)
{
    if (ParentChessBoard == nullptr) {
        throw UnsetParentChessboard();
    }
    _ParentChessBoard = ParentChessBoard;
}

void Tile::initTile()
{
    if (_ParentChessBoard == nullptr) {
       throw UnsetParentChessboard();
    }
    _SceneManager = _ParentChessBoard->getParentWindow()->getSceneManager();
    _Driver = _ParentChessBoard->getParentWindow()->getDriver();
    _Device = _ParentChessBoard->getParentWindow()->getDevice();
}

void Tile::createTile()
{
    std::cout << "Tile: Creating tile on pos " << _X << " " << _Y << std::endl;
    if (_SceneManager == nullptr || _Driver == nullptr || _Device == nullptr) {
        throw UnsetIrrlichVar();
    }
    if (_X == -1 || _Y == -1 || _Z == -1) {
        throw UnsetPos();
    }
    if (_TileSize == -1) {
        throw UnsetTileSize();
    }
    _Node = const_cast<irr::scene::ISceneManager*>(_SceneManager)->addCubeSceneNode(_TileSize);
    if (_Node == nullptr) {
        throw UnsetNode();
    }
    _Node->setMaterialTexture(0, _TileTexture);
    _Node->setPosition(irr::core::vector3df(_X * _TileSize, _TileSize / 2, _Y * _TileSize));
    _Node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _Node->setMaterialTexture(0, _TileTexture);
    _Node->setMaterialType(irr::video::EMT_SOLID);
    _Node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
}


void Tile::setTexture(irr::video::ITexture* tileTexture)
{
    _TileTexture = tileTexture;
}

void Tile::setPos(int x, int y, int z)
{
    if (x != -1)
        _X = x;
    if (y != -1)
        _Y = y;
    if (z != -1)
        _Z = z;
}

void Tile::setTileSize(float tileSize)
{
    _TileSize = tileSize;
}

void Tile::setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    _food = food;
    _linemate = linemate;
    _deraumere = deraumere;
    _sibur = sibur;
    _mendiane = mendiane;
    _phiras = phiras;
    _thystame = thystame;
}

void Tile::printInventory()
{
    std::cout << "food: " << _food << std::endl;
    std::cout << "linemate: " << _linemate << std::endl;
    std::cout << "deraumere: " << _deraumere << std::endl;
    std::cout << "sibur: " << _sibur << std::endl;
    std::cout << "mendiane: " << _mendiane << std::endl;
    std::cout << "phiras: " << _phiras << std::endl;
    std::cout << "thystame: " << _thystame << std::endl;
}

void Tile::setPlayer(int player)
{
    _player = player;
}

void Tile::setEgg(int egg)
{
    _egg = egg;
}

irr::scene::ISceneNode *Tile::getNode()
{
    return _Node;
}

int Tile::getPlayer()
{
    return _player;
}

int Tile::getEgg()
{
    return _egg;
}

chessBoard *Tile::getParentChessBoard()
{
    if (_ParentChessBoard == nullptr) {
        throw UnsetParentChessboard();
    }
    return _ParentChessBoard;
}

int Tile::getPositionX()
{
    return _X;
}

int Tile::getPositionY()
{
    return _Y;
}

int Tile::getPositionZ()
{
    return _Z;
}

std::vector<int> Tile::getInventory()
{
    std::vector<int> inventory = {_food, _linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame};
    return inventory;
}
