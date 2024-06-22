/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#include "irrlichtEventHandler.hpp"
#include <iostream>

myEventReceiver::myEventReceiver(irrlichtWindow* parentWindow)
{
    if (parentWindow == nullptr) {
        throw NullableDevice();
    }
    _ParentWindow = parentWindow;
    _LeftMouseButtonDown = false;
    _RightMouseButtonDown = false;
    _ActiveCamera = nullptr;
}

myEventReceiver::~myEventReceiver()
{
    if (_ActiveCamera != nullptr) {
        _ActiveCamera->drop();
        _ActiveCamera = nullptr;
    }
    for (auto tile : _Tiles) {
        delete tile;
    }
    _Tiles.clear();
}

void myEventReceiver::InitEventReceiver()
{
    _Device = _ParentWindow->getDevice();
    if (_Device == nullptr) {
        throw UnsetDevice();
    }
    _SceneManager = _ParentWindow->getSceneManager();
    if (_SceneManager == nullptr) {
        throw UnsetSceneManager();
    }
    _Driver = _ParentWindow->getDriver();
    if (_Driver == nullptr) {
        throw UnsetDriver();
    }
    _ActiveCamera = _ParentWindow->getActiveCamera();
    if (_ActiveCamera == nullptr) {
        throw UnsetCamera();
    }
    _ActiveCamera->grab();
}

void myEventReceiver::addTile(Tile* tile)
{
    if (tile == nullptr) {
        throw NullTile();
    }
    _Tiles.push_back(tile);
}

void myEventReceiver::addPlayer(Player* player)
{
    if (player == nullptr) {
        throw NullPlayer();
    }
    _Players.push_back(player);
}

bool myEventReceiver::OnEvent(const irr::SEvent& event)
{
    if (_ActiveCamera && _ActiveCamera->OnEvent(event)) {
        return true;
    }
    if (_Device == nullptr) {
        throw UnsetDevice();
    }
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        return mouseClick(event);
    }
    if (event.EventType != irr::EET_KEY_INPUT_EVENT)
        return false;
    if (event.KeyInput.PressedDown)
        return keyPress(event);
    return false;
}

bool myEventReceiver::keyPress(const irr::SEvent& event)
{
    irr::EKEY_CODE keyCode = event.KeyInput.Key;

    if (keyCode == irr::KEY_ESCAPE) {
        if (_Device->isWindowActive())
            _Device->closeDevice();
        return true;
    }

    if (keyCode == irr::KEY_KEY_P) {
        const irr::core::vector3df& position = _ActiveCamera->getPosition();
        const irr::core::vector3df& target = _ActiveCamera->getTarget();
        std::cout << "Position: (" << position.X << ", " << position.Y << ", " << position.Z << ")" << std::endl;
        std::cout << "Target: (" << target.X << ", " << target.Y << ", " << target.Z << ")" << std::endl;
        return false;
    }
    return false;
}

bool myEventReceiver::mouseClick(const irr::SEvent& event)
{
    if (event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP) {
        this->_RightMouseButtonDown = false;
        return OnRightMouseClick(event.MouseInput);
    } else if (event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN) {
        this->_RightMouseButtonDown = true;
    }
    if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP) {
        this->_LeftMouseButtonDown = false;
        return OnLeftMouseClick(event.MouseInput);
    } else if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN) {
        this->_LeftMouseButtonDown = true;
    }
    return false;
}

bool myEventReceiver::OnRightMouseClick(const irr::SEvent::SMouseInput& mouseInput)
{
    (void) mouseInput;
    return false;
}

bool myEventReceiver::OnLeftMouseClick(const irr::SEvent::SMouseInput& mouseInput)
{
    if (CheckIfTileIsClicked(mouseInput)) {
        return true;
    }
    return false;
}

bool myEventReceiver::CheckIfTileIsClicked(const irr::SEvent::SMouseInput& mouseInput)
{
    irr::core::line3d<irr::f32> ray = _SceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(irr::core::position2di(mouseInput.X, mouseInput.Y), _ActiveCamera);
    for (auto player : _Players) {
        if (CheckIfNodeIsClicked(ray, player->getChessPieceNode())) {
            player->printInventory();
            return true;
        }
    }
    for (auto tile : _Tiles) {
        if (CheckIfSimpleNodeIsClicked(ray, tile->getNode())) {
            tile->printInventory();
            return true;
        }
    }
    return false;
}

bool myEventReceiver::CheckIfSimpleNodeIsClicked(irr::core::line3d<irr::f32> ray, irr::scene::ISceneNode *node)
{
    if (node == nullptr)
        return false;
    irr::scene::IMeshSceneNode* meshNode = static_cast<irr::scene::IMeshSceneNode*>(node);
    if (!meshNode->getTriangleSelector()) {
        meshNode->setTriangleSelector(_SceneManager->createTriangleSelector(meshNode->getMesh(), meshNode));
    }
    irr::core::vector3df intersection;
    irr::core::triangle3df hitTriangle;
    irr::scene::ISceneNode* hitNode = nullptr;
    if (_SceneManager->getSceneCollisionManager()->getCollisionPoint(ray, meshNode->getTriangleSelector(), intersection, hitTriangle, hitNode)) {
        return true;
    }
    return false;
}

bool myEventReceiver::CheckIfNodeIsClicked(irr::core::line3d<irr::f32> ray, irr::scene::IAnimatedMeshSceneNode *node)
{
    if (node == nullptr)
        return false;
    irr::scene::IAnimatedMeshSceneNode* animNode = static_cast<irr::scene::IAnimatedMeshSceneNode*>(node);
    if (!animNode->getTriangleSelector()) {
        animNode->setTriangleSelector(_SceneManager->createTriangleSelectorFromBoundingBox(animNode));
    }
    irr::core::vector3df intersection;
    irr::core::triangle3df hitTriangle;
    irr::scene::ISceneNode* hitNode = nullptr;
    if (_SceneManager->getSceneCollisionManager()->getCollisionPoint(ray, animNode->getTriangleSelector(), intersection, hitTriangle, hitNode)) {
        return true;
    }
    return false;
}
