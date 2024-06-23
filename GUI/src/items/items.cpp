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
    _Food = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/cake/cake.obj");
    _Linemate = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/coal/coal.obj");
    _Deraumere = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/diamond/diamond.obj");
    _Sibur = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/emerald/emerald.obj");
    _Mendiane = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/gold/gold.obj");
    _Phiras = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/iron/iron.obj");
    _Thystame = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj/items/netherite/netherite.obj");
    _Egg = _ParentchessBoard->getParentWindow()->getObjLoader()->loadObj("./GUI/assets/obj//items/egg/egg.obj");
}

void items::setParentchessBoard(chessBoard *ParentchessBoard)
{
    _ParentchessBoard = ParentchessBoard;
}

std::vector<bool> items::CompareInvAndMesh(std::vector<int> inventory, std::vector<int> &meshInventory, int eggInInventory)
{
    std::vector<bool> diff;
    for (int i = 0; i < 7; i++) {
        if ((inventory[i] >  0) == (meshInventory[i] > 0))
            diff.push_back(true);
        else
            diff.push_back(false);
        meshInventory[i] = inventory[i];
    }
    if ((eggInInventory > 0) == (meshInventory[7] > 0))
        diff.push_back(true);
    else
        diff.push_back(false);
    meshInventory[7] = eggInInventory;
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
    float offsetX = 0;
    float offsetY = 0;
    for (int i = 0; i < 7; i++) {
        if (node[i] != nullptr && inventory[i] == 0) {
            node[i]->remove();
            node[i] = nullptr;
        } else if (node[i] == nullptr && inventory[i] > 0) {
            switch (i) {
                case 0:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Food);
                    node[i]->setScale(irr::core::vector3df(4, 1, 4)); // ny = 31
                    offsetX = 0;
                    offsetY = 10;
                    break;
                case 1:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Linemate);
                    node[i]->setScale(irr::core::vector3df(2, 1, 2)); // ny = 30
                    offsetX = 10;
                    offsetY = 10;
                    break;
                case 2:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Deraumere); // lag with it
                    node[i]->setScale(irr::core::vector3df(0.04, 0.04, 0.04)); // ny = 32.5
                    offsetX = 10;
                    offsetY = -10;
                    break;
                case 3:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Sibur);
                    node[i]->setScale(irr::core::vector3df(0.01, 0.01, 0.01)); // ny = 32
                    offsetX = -10;
                    offsetY = -10;
                    break;
                case 4:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Mendiane);
                    node[i]->setScale(irr::core::vector3df(0.01, 0.01, 0.01)); // ny = 32
                    offsetX = -10;
                    offsetY = 10;
                    break;
                case 5:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Phiras);
                    node[i]->setScale(irr::core::vector3df(0.01, 0.01, 0.01)); // ny = 32
                    offsetX = 0;
                    offsetY = -10;
                    break;
                case 6:
                    node[i] = _SceneManager->addAnimatedMeshSceneNode(_Thystame);
                    node[i]->setScale(irr::core::vector3df(0.09, 0.09, 0.09)); // ny = 33
                    offsetX = 0;
                    offsetY = 10;
                    break;
            }
            node[i]->setPosition(irr::core::vector3df(
                x * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize() + offsetX,
                (i == 0) ? 31 : (i == 1) ? 30 : (i == 2) ? 32.5 : (i == 3) ? 32 : (i == 4) ? 32 : (i == 5) ? 32 : (i == 6) ? 33 : 0,
                y * _ParentchessBoard->getParentWindow()->getLinkedZappyGame()->getTileSize() + offsetY
            ));
        }
    }
}

void items::updateText(Tile *tile, std::vector<int> inventory, bool debug)
{
    if (_TextNode[tile->getPositionX()][tile->getPositionY()] != nullptr) {
        _TextNode[tile->getPositionX()][tile->getPositionY()]->remove();
        _TextNode[tile->getPositionX()][tile->getPositionY()] = nullptr;
    }
    if (!debug)
        return;
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
        _DisplayNode.resize( _ParentchessBoard->getParentWindow()->getWidth());
        for (int i = 0; i < _ParentchessBoard->getParentWindow()->getWidth(); i++) {
            _ItemNode[i].resize(_ParentchessBoard->getParentWindow()->getHeight());
            _TextNode[i].resize(_ParentchessBoard->getParentWindow()->getHeight());
            _DisplayNode[i].resize(_ParentchessBoard->getParentWindow()->getHeight());
            for (int j = 0; j < _ParentchessBoard->getParentWindow()->getHeight(); j++) {
                _DisplayNode[i][j].resize(8);
                for (int k = 0; k < 8; k++) {
                    _DisplayNode[i][j][k] = 0;
                }
            }
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
            std::vector<bool> diff = CompareInvAndMesh(inventory, _DisplayNode[tile->getPositionX()][tile->getPositionY()], tile->getEgg());
            updateText(tile, inventory, _ParentchessBoard->getParentWindow()->getEventReceiver()->getDebug());
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
