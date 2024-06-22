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
    _TextNode.clear();
    _ItemNode.clear();
    
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
    _Food = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/cake/cake.obj");
    _Font = _ParentchessBoard->getParentWindow()->getGuiEnv()->getBuiltInFont();
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
    if (_Font == nullptr) {
        throw UnsetFont();
    }


    
    _TextNode.clear();

    _ItemNode.clear();
    float TileSize = _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize();
    for (const auto& line : map) {
        for (const auto& tile : line) {
            if (tile == nullptr) {
                continue;
            }
            std::cout << " tile on x: " << tile->getPositionX() << " y: " << tile->getPositionY() << " z: " << tile->getPositionZ() << " has " << std::endl;
            std::vector<int> inventory = tile->getInventory();
            std::string text = " food : " + std::to_string(inventory[0]) + "\nlinemate : " + std::to_string(inventory[1]) + "\nderaumere : " + std::to_string(inventory[2]) + "\nsibur : " + std::to_string(inventory[3]) + "\nmendiane : " + std::to_string(inventory[4]) + "\nphiras : " + std::to_string(inventory[5]) + "\nthystame : " + std::to_string(inventory[6]);
            // _TextNode.push_back(_SceneManager->addTextSceneNode(
            //     _Font,
            //     irr::core::stringw(text.c_str()).c_str(),
            //     irr::video::SColor(255, 155, 0, 0),
            //     0,
            //     irr::core::vector3df(
            //         tile->getPositionX() * TileSize,
            //         30,
            //         tile->getPositionY() * TileSize
            //     )
            // ));
            if (inventory[0] != 0) {
                _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Food));
                _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
                _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 40 , tile->getPositionY() * TileSize));
            }
            // if (inventory[1] != 0) {
            //     _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Linemate));
            //     _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            //     _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
            //     _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 30 , tile->getPositionY() * TileSize));
            // }
            // if (inventory[2] != 0) {
            //     _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Deraumere));
            //     _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            //     _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
            //     _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 30 , tile->getPositionY() * TileSize));
            // }
            // if (inventory[3] != 0) {
            //     _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Sibur));
            //     _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            //     _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
            //     _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 30 , tile->getPositionY() * TileSize));
            // }
            // if (inventory[4] != 0) {
            //     _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Mendiane));
            //     _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            //     _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
            //     _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 30 , tile->getPositionY() * TileSize));
            // }
            // if (inventory[5] != 0) {
            //     _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Phiras));
            //     _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            //     _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
            //     _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 30 , tile->getPositionY() * TileSize));
            // }
            // if (inventory[6] != 0) {
            //     _ItemNode.push_back(_SceneManager->addAnimatedMeshSceneNode(_Thystame));
            //     _ItemNode.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            //     _ItemNode.back()->setScale(irr::core::vector3df(10.0f, 10.0f, 10.0f));
            //     _ItemNode.back()->setPosition(irr::core::vector3df(tile->getPositionX() * TileSize , 30 , tile->getPositionY() * TileSize));
            // }
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
