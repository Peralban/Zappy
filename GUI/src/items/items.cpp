/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** items
*/

#include "items.hpp"
#include <thread>

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
    _Font = _ParentchessBoard->getParentWindow()->getGuiEnv()->getBuiltInFont();
    _Food = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Linemate = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Deraumere = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Sibur = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Mendiane = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Phiras = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Thystame = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
    _Egg = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/cube.obj");
}

std::vector<int> items::getMeshInventory(std::array<irr::scene::IAnimatedMeshSceneNode *, 8> node)
{
    std::vector<int> inventory;
    for (int i = 0; i < 8; i++) {
        if (node[i] != nullptr)
            inventory.push_back(1);
        else
            inventory.push_back(0);
    }
    return inventory;
}

void items::setParentchessBoard(chessBoard *ParentchessBoard)
{
    _ParentchessBoard = ParentchessBoard;
}

std::vector<bool> items::CompareInvAndMesh(std::vector<int> inventory, std::vector<int> meshInventory, int eggInInventory)
{
    std::vector<bool> diff;
    for (int i = 0; i < 7; i++) {
        if ((inventory[i] >  0) != (meshInventory[i] > 0))
            diff.push_back(true);
        else
            diff.push_back(false);
    }
    if (eggInInventory > 0 && meshInventory[7] == 1)
        diff.push_back(true);
    else
        diff.push_back(false);
    return diff;
}

bool items::isSameInventory(std::vector<bool> inventory)
{
    for (int i = 0; i < 7; i++) {
        if (!inventory[i])
            return false;
    }
    return true;
}

void items::updateMesh(std::array<irr::scene::IAnimatedMeshSceneNode *, 8> node, std::vector<int> inventory, int x, int y)
{
    for (int i = 0; i < 7; i++) {
        if (node[i] != nullptr && inventory[i] == 0) {
            node[i]->remove();
            node[i] = nullptr;
        } else if (node[i] == nullptr && inventory[i] > 0) {
            switch (i) {
                case 0:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Food);
                    break;
                case 1:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Linemate);
                    break;
                case 2:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Deraumere);
                    break;
                case 3:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Sibur);
                    break;
                case 4:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Mendiane);
                    break;
                case 5:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Phiras);
                    break;
                case 6:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Thystame);
                    break;
            }
            node[i]->setPosition(irr::core::vector3df(
                x * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize(),
                0,
                y * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize()
            ));
            node[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node[i]->setScale(irr::core::vector3df(3.5f, 3.5f, 3.5f));
        }
    }
    if (node[7] != nullptr && inventory[7] == 0) {
        node[7]->remove();
        node[7] = nullptr;
    } else if (node[7] == nullptr && inventory[7] > 0) {
        node[7] = _SceneManager->addAnimatedMeshSceneNode(_Egg);
        node[7]->setPosition(irr::core::vector3df(
            x * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize(),
            0,
            y * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize()
        ));
    }
}

void items::updateText(Tile *tile, std::vector<int> inventory)
{
    if (_TextNode[tile->getPositionX()][tile->getPositionY()] != nullptr) {
        _TextNode[tile->getPositionX()][tile->getPositionY()]->remove();
        _TextNode[tile->getPositionX()][tile->getPositionY()] = nullptr;
    }
    std::string text = " food : " + std::to_string(inventory[0]) + "\nlinemate : " + std::to_string(inventory[1]) + "\nderaumere : " + std::to_string(inventory[2]) + "\nsibur : " + std::to_string(inventory[3]) + "\nmendiane : " + std::to_string(inventory[4]) + "\nphiras : " + std::to_string(inventory[5]) + "\nthystame : " + std::to_string(inventory[6]);
    _TextNode[tile->getPositionX()][tile->getPositionY()] = _SceneManager->addTextSceneNode(
        _Font,
        irr::core::stringw(text.c_str()).c_str(),
        irr::video::SColor(255, 155, 0, 0),
        0,
        irr::core::vector3df(
            tile->getPositionX() * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize(),
            30,
            tile->getPositionY() * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize()
        )
    );
}

void items::updateMap(std::vector<std::vector<Tile *>> map)
{
    static bool first = true;

    if (first) {
        _ItemNode.resize( _ParentchessBoard->getParentWindow()->getWidth());
        _TextNode.resize( _ParentchessBoard->getParentWindow()->getWidth());
        for (int i = 0; i < _ParentchessBoard->getParentWindow()->getWidth(); i++) {
            _ItemNode[i].resize(_ParentchessBoard->getParentWindow()->getHeight());
            _TextNode[i].resize(_ParentchessBoard->getParentWindow()->getHeight());
        }
        first = false;
    }
    if (_ParentchessBoard == nullptr)
        throw UnsetParentchessBoard();
    if (_SceneManager == nullptr)
        throw UnsetNode();
    if (_Device == nullptr)
        throw UnsetDevice();
    if (_Driver == nullptr)
        throw UnsetDriver();
    if (_Font == nullptr)
        throw UnsetFont();
    size_t maxThreads = (size_t)std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    for (const auto& line : map) {
        for (const auto& tile : line) {
            if (tile == nullptr)
                continue;
            std::vector<int> inventory = tile->getInventory();
            std::vector<int> meshInventory = getMeshInventory(_ItemNode[tile->getPositionX()][tile->getPositionY()]);
            std::vector<bool> diff = CompareInvAndMesh(inventory, meshInventory, tile->getEgg());
            updateText(tile, inventory);
            if(!isSameInventory(diff))
                threads.push_back(std::thread(&items::updateMesh, this, _ItemNode[tile->getPositionX()][tile->getPositionY()], inventory, tile->getPositionX(), tile->getPositionY()));
            if (threads.size() >= maxThreads || (tile->getPositionX() == (int)map.size() - 1 && tile->getPositionY() == (int)map[0].size() - 1)) {
                for (auto& thread : threads) {
                    thread.join();
                }
                threads.clear();
            }
        }
    }
}
