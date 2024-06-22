/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** items
*/

#include "items.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"

items::items()
{
}

items::items(chessBoard *ParentChessboard)
{
    _ParentchessBoard = ParentChessboard;
    _SceneManager = _ParentchessBoard->getParentWindow()->getSceneManager();
    _Driver = _ParentchessBoard->getParentWindow()->getDriver();
    _Device = _ParentchessBoard->getParentWindow()->getDevice();
}

items::~items()
{
}

void items::initItemsObj()
{
    //_Food = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/cake/cake.obj");
    _Linemate = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/coal/coal.obj");
    _Deraumere = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/iron/iron.obj");
    _Sibur = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/gold/gold.obj");
    _Mendiane = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/emerald/emerald.obj");
    _Phiras = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/diamond/diamond.obj");
    _Thystame = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/netherite/netherite.obj");
}

void items::setParentchessBoard(chessBoard *ParentchessBoard)
{
    _ParentchessBoard = ParentchessBoard;
}

void items::updateMap(std::vector<std::vector<Tile *>> map)
{
    if (_ParentchessBoard == nullptr) {
        throw UnsetParentchessBoard();
    }
    if (_SceneManager == nullptr) {
        throw UnsetNode();
    }
    if (_Device == nullptr) {
        throw UnsetDevice();
    }
    if (_Driver == nullptr) {
        throw UnsetDriver();
    }
    for (const auto& line : map) {
        for (const auto& tile : line) {
            if (tile == nullptr) {
                continue;
            }
            std::cout << " tile on x: " << tile->getPositionX() << " y: " << tile->getPositionY() << " z: " << tile->getPositionZ() << " has " << std::endl;
            std::vector<int> inventory = tile->getInventory();
            std::cout << inventory[0] << " food" << std::endl;
            std::cout << inventory[1] << " linemate" << std::endl;
            std::cout << inventory[2] << " deraumere" << std::endl;
            std::cout << inventory[3] << " sibur" << std::endl;
            std::cout << inventory[4] << " mendiane" << std::endl;
            std::cout << inventory[5] << " phiras" << std::endl;
            std::cout << inventory[6] << " thystame" << std::endl;

        }
    }
}
