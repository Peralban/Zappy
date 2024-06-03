/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#include "zappyIrrlicht/irrlichtWindow.hpp"

irrlichtWindow::irrlichtWindow(
    int width, int height,
    int platformX, int platformY,
    float tileSize, video::E_DRIVER_TYPE driverType = video::EDT_OPENGL)
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
    this->_Quality = MidPoly;
}

void irrlichtWindow::windowCreateDevice()
{
	IrrlichtDevice *device = createDevice(this->_DriverType, core::dimension2d<u32>(this->_Width, this->_Height), 16, false, false, false, 0);
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
	activeCamera->setPosition(core::vector3df(-15, height, -15));
	activeCamera->setTarget(core::vector3df(50, 35, 50));
	activeCamera->setFarValue(10000.0f);
	activeCamera->setNearValue(0.1f);
	activeCamera->setAspectRatio(1.33f);
	activeCamera->setInputReceiverEnabled(true);
	activeCamera->setDebugDataVisible(scene::EDS_FULL);
	activeCamera->setViewMatrixAffector(core::matrix4());
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
	std::cout << "chessBoard created" << std::endl;
}

int irrlichtWindow::runWindow()
{
    while(this->_Device->run()) {
        if (this->_Device->isWindowActive()) {
        	this->_Driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
            this->_SceneManager->drawAll();
            this->_Driver->endScene();
        }
        else
            this->_Device->yield();
    }
    return 0;
}

IrrlichtDevice *irrlichtWindow::getDevice()
{
    return this->_Device;
}

IVideoDriver *irrlichtWindow::getDriver()
{
    return this->_Driver;
}

ISceneManager *irrlichtWindow::getSceneManager()
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

