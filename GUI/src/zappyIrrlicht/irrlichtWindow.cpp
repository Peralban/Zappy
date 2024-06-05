/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#include "irrlichtWindow.hpp"
#include <iostream>

irrlichtWindow::irrlichtWindow(
    int width, int height,
    int platformX, int platformY,
    float tileSize, irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL,
    quality selectedQuality = MID, bool debug = false)
{
    this->_Width = width;
    this->_Height = height;
    this->_PlatformX = platformX;
    this->_PlatformY = platformY;
    this->_TileSize = tileSize;
    this->_DriverType = driverType;
    this->_Device = nullptr;
    this->_Driver = nullptr;
    this->_SceneManager = nullptr;
    this->_chessBoard = nullptr;
    this->_EventReceiver = nullptr;
    this->_LinkedZappyGame = nullptr;
    this->_Quality = selectedQuality;
    this->_Debug = debug;
}

void irrlichtWindow::windowCreateDevice()
{
    irr::IrrlichtDevice *device = irr::createDevice(this->_DriverType, irr::core::dimension2d<irr::u32>(this->_Width, this->_Height), 16, false, false, false, 0);
	if (device == 0) {
        this->_Device = nullptr;
		return;
    }
	this->_Device = device;
}

irrlichtWindow::~irrlichtWindow()
{
    this->_Device->drop();
}

void irrlichtWindow::initDrivers()
{
    this->_Driver = this->_Device->getVideoDriver();
    this->_SceneManager = this->_Device->getSceneManager();
}

void irrlichtWindow::initCamera()
{
    int height = (this->_PlatformX + this->_PlatformY) * 3 + 25;

	this->_Device->getCursorControl()->setVisible(false);

	this->_SceneManager->addCameraSceneNodeFPS();
    auto activeCamera = this->_SceneManager->getActiveCamera();
	// droite-gauche   haut-bas   avant-arriere
	activeCamera->setPosition(irr::core::vector3df(-15, height, -15));
	activeCamera->setTarget(irr::core::vector3df(50, 35, 50));
	activeCamera->setFarValue(10000.0f);
	activeCamera->setNearValue(0.1f);
	activeCamera->setAspectRatio(1.33f);
	activeCamera->setInputReceiverEnabled(true);
	activeCamera->setDebugDataVisible(irr::scene::EDS_FULL);
	activeCamera->setViewMatrixAffector(irr::core::matrix4());
    if (this->_Debug)
        std::cout << "Camera initialized" << std::endl;
}

void irrlichtWindow::initEventReceiver()
{
    _EventReceiver = new myEventReceiver(_Device);
    _Device->setEventReceiver(_EventReceiver);
}

void irrlichtWindow::initChessBoard()
{
    this->_chessBoard = new chessBoard(this->_SceneManager, this->_Driver, this->_PlatformX, this->_PlatformY, this->_TileSize);
    this->_chessBoard->createBoard();
    if (this->_Debug)
	    std::cout << "chessBoard created" << std::endl;
}

int irrlichtWindow::runWindow()
{
    while(this->_Device->run()) {
        if (this->_Device->isWindowActive()) {
        	this->_Driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
            this->_SceneManager->drawAll();
            this->_Driver->endScene();
        }
        else
            this->_Device->yield();
    }
    return 0;
}

irr::IrrlichtDevice *irrlichtWindow::getDevice()
{
    return this->_Device;
}

irr::video::IVideoDriver *irrlichtWindow::getDriver()
{
    return this->_Driver;
}

irr::scene::ISceneManager *irrlichtWindow::getSceneManager()
{
    return this->_SceneManager;
}

quality irrlichtWindow::getQuality()
{
    return this->_Quality;
}

void irrlichtWindow::linkZappyGame(ZappyGame *gameToLink)
{
    this->_LinkedZappyGame = gameToLink;
    gameToLink->linkWithDevice(this);
}

ZappyGame *irrlichtWindow::getLinkedZappyGame()
{
    return this->_LinkedZappyGame;
}

int irrlichtWindow::getWidth()
{
    return this->_Width;
}

int irrlichtWindow::getHeight()
{
    return this->_Height;
}

int irrlichtWindow::getPlatformX()
{
    return this->_PlatformX;
}

int irrlichtWindow::getPlatformY()
{
    return this->_PlatformY;
}

float irrlichtWindow::getTileSize()
{
    return this->_TileSize;
}

bool irrlichtWindow::getDebugState()
{
    return this->_Debug;
}
