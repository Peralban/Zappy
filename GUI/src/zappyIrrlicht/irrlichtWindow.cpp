/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#include "irrlichtWindow.hpp"
#include "networkGui/guiClient.hpp"
#include <iostream>

irrlichtWindow::irrlichtWindow(
    int width, int height,
    irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL,
    quality selectedQuality = MID, bool debug = false)
{
    this->_Width = width;
    this->_Height = height;
    this->_DriverType = driverType;
    this->_Device = nullptr;
    this->_Driver = nullptr;
    this->_SceneManager = nullptr;
    this->_EventReceiver = nullptr;
    this->_LinkedZappyGame = nullptr;
    this->_Quality = selectedQuality;
    this->_Debug = debug;
    this->_ServerAdress = nullptr;
    this->_ServerPort = 0;
    this->_ObjLoader = nullptr;
    this->_TextureLoader = nullptr;
    this->_ActiveCamera = nullptr;
    this->_CursorLength = 0;
    this->_CursorThickness = 0;
    this->_CursorColor = irr::video::SColor(255, 0, 0, 0);
    
}

void irrlichtWindow::parseArgs(int ac, char **av)
{
    if (ac != 3) {
        throw WrongArgs();
    }
    std::regex ip_regex(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})");
    if (!std::regex_match(av[1], ip_regex)) {
        throw InvalidIP();
    }
    if (std::stoi(av[2]) < 1024 || std::stoi(av[2]) > 65535) {
        throw InvalidPort();
    }
    this->_ServerAdress = av[1];
    this->_ServerPort = std::stoi(av[2]);
}

void irrlichtWindow::windowCreateDevice()
{
    irr::IrrlichtDevice *device = irr::createDevice(this->_DriverType, irr::core::dimension2d<irr::u32>(this->_Width, this->_Height), 16, false, false, false, 0);
	if (device == 0) {
        throw NotDeviceCreated();
    }
	this->_Device = device;
}

irrlichtWindow::~irrlichtWindow()
{
    this->_Device->drop();
}

void irrlichtWindow::initDrivers()
{
    if (!this->_Device) {
        throw DeviceUninitialized();
    }
    this->_Driver = this->_Device->getVideoDriver();
    this->_SceneManager = this->_Device->getSceneManager();
}

void irrlichtWindow::initLoader()
{
    this->_ObjLoader = new ObjLoader(this->_SceneManager);
    this->_TextureLoader = new TextureLoader(this->_Driver);
}

void irrlichtWindow::initCamera()
{
    //making the height of the camera relative to the platform size
    int height = 25;


	this->_ActiveCamera = this->_SceneManager->addCameraSceneNodeFPS(0, 40.f, 50.f, -1, 0, 0, true, 0.5f, false, true);
    if (this->_ActiveCamera == nullptr) {
        throw UnableToCreateCamera();
    }
    this->_Device->getCursorControl()->setVisible(false);

	// droite-gauche   haut-bas   avant-arriere
	this->_ActiveCamera->setPosition(irr::core::vector3df(-15, height, -15));
	this->_ActiveCamera->setTarget(irr::core::vector3df(50, 35, 50));
	this->_ActiveCamera->setFarValue(10000.0f);
	this->_ActiveCamera->setNearValue(0.1f);
	this->_ActiveCamera->setAspectRatio(1.33f);
	this->_ActiveCamera->setDebugDataVisible(irr::scene::EDS_FULL);
    if (this->_Debug)
        std::cout << "Camera initialized" << std::endl;
}

void irrlichtWindow::initCursor(int cursorLength, int thickness, irr::video::SColor cursorColor)
{
    this->_CursorLength = cursorLength;
    this->_CursorColor = cursorColor;
    this->_CursorThickness = thickness;
}

void irrlichtWindow::initCursor(int cursorLength, int thickness, int red, int green, int blue)
{
    this->_CursorLength = cursorLength;
    this->_CursorThickness = thickness;
    this->_CursorColor = irr::video::SColor(255, red, green, blue);
}

void irrlichtWindow::setCursorLength(int cursorLength)
{
    this->_CursorLength = cursorLength;
}

void irrlichtWindow::setCursorThickness(int thickness)
{
    this->_CursorThickness = thickness;
}

void irrlichtWindow::drawCursor()
{
    
    irr::core::dimension2d<irr::u32> screenSize = _Driver->getScreenSize();
    int screenWidth = screenSize.Width;
    int screenHeight = screenSize.Height;
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;
    _Driver->draw2DRectangle(_CursorColor, irr::core::rect<irr::s32>(centerX - _CursorLength, centerY - _CursorThickness, centerX + _CursorLength, centerY + _CursorThickness)); // Horizontal line
    _Driver->draw2DRectangle(_CursorColor, irr::core::rect<irr::s32>(centerX - _CursorThickness, centerY - _CursorLength, centerX + _CursorThickness, centerY + _CursorLength)); // Vertical line
}

void irrlichtWindow::LinkEventReceiver()
{
    this->_EventReceiver = new myEventReceiver(this);
    if (this->_EventReceiver == nullptr) {
        throw UnableToCreateEvent();
    }
    this->_Device->setEventReceiver(this->_EventReceiver);
    this->_EventReceiver->InitEventReceiver();
}

char *irrlichtWindow::getServerAdress()
{
    if (!this->_ServerAdress) {
        throw UninitializedServerAdress();
    }
    return this->_ServerAdress;
}

int irrlichtWindow::getServerPort()
{
    if (this->_ServerPort < 1024 || this->_ServerPort > 65535) {
        throw InvalidPort();
    }
    return this->_ServerPort;
}

int irrlichtWindow::runWindow(ZappyGame *game, guiNetworkClient *client)
{
    (void) game;
    (void) client;
    int count = 0;
    while(this->_Device->run()) {
       
        for (int i = 0; i < 100; i++)
            this->_LinkedGuiClient->selectSocket();
        if (this->_Device->isWindowActive()) {
            // make the player rotate
            float orientation = this->getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->getConvOrientationX();
            if (orientation >= 359)
                this->getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setConvertedOrientationX(0);
            else
                this->getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setConvertedOrientationX(orientation + 1);

            // update the player position BUT NOT THE CONV POSITION
            this->getLinkedZappyGame()->getPlayer("player1")->updatePlayerPos();
            if (count < 100) {
                count++;
            } else {

                this->getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setPos(rand() % this->getLinkedZappyGame()->getPlatformWidth(), rand() % this->getLinkedZappyGame()->getPlatformHeight(), 3);
                count = 0;
            }
        	this->_Driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
            this->_SceneManager->drawAll();
            this->drawCursor();
            this->_Driver->endScene();
        } else
            this->_Device->yield();
    }
    return 0;
}

irr::scene::ICameraSceneNode *irrlichtWindow::getActiveCamera()
{
    if (!this->_ActiveCamera) {
        throw UninitializedCamera();
    }
    return this->_ActiveCamera;
}

irr::IrrlichtDevice *irrlichtWindow::getDevice()
{
    if (!this->_Device) {
        throw DeviceUnitialized();
    }
    return this->_Device;
}

irr::video::IVideoDriver *irrlichtWindow::getDriver()
{
    if (!this->_Driver) {
        throw DriverUnitialized();
    }
    return this->_Driver;
}

irr::scene::ISceneManager *irrlichtWindow::getSceneManager()
{
    if (!this->_SceneManager) {
        throw SceneManagerUnitialized();
    }
    return this->_SceneManager;
}

quality irrlichtWindow::getQuality()
{
    if (!this->_Quality) {
        std::cout << "getQuality: Warning: Quality not initialized returning default value : LOW" << std::endl;
        return LOW;
    }
    return this->_Quality;
}

void irrlichtWindow::linkZappyGame(ZappyGame *gameToLink)
{
    if (!gameToLink) {
        throw UnlinkedZappyGame();
    }
    this->_LinkedZappyGame = gameToLink;
    gameToLink->linkWithDevice(this);
}

void irrlichtWindow::linkGuiClient(guiNetworkClient *clientToLink)
{
    if (!this->_LinkedZappyGame) {
        throw UnlinkedZappyGame();
    }
    if (!clientToLink) {
        throw UnlinkedGuiNetworkClient();
    }
    this->_LinkedGuiClient = clientToLink;
    clientToLink->setLinkedGame(this);
    if (this->_LinkedZappyGame->getServerDataParser() == nullptr) {
        throw UnlinkedServerDataParser();
    }
    this->_LinkedZappyGame->getServerDataParser()->SetParentClient(clientToLink);
}

ZappyGame *irrlichtWindow::getLinkedZappyGame()
{
    if (!this->_LinkedZappyGame) {
        throw UninitializedZappyGame();
    }
    return this->_LinkedZappyGame;
}

guiNetworkClient *irrlichtWindow::getGuiClient()
{
    if (!this->_LinkedGuiClient) {
        throw UninitializedGuiNetworkClient();
    }
    return this->_LinkedGuiClient;
}

ObjLoader *irrlichtWindow::getObjLoader()
{
    if (this->_ObjLoader == nullptr) {
        throw UninitializedObjLoader();
    }
    return this->_ObjLoader;
}

TextureLoader *irrlichtWindow::getTextureLoader()
{
    if (!this->_TextureLoader) {
        throw ObjLoader();
    }
    return this->_TextureLoader;
}

myEventReceiver *irrlichtWindow::getEventReceiver()
{
    if (!this->_EventReceiver) {
        // TODO add a throw
    }
    return this->_EventReceiver;
}

int irrlichtWindow::getWidth()
{
    return this->_Width;
}

int irrlichtWindow::getHeight()
{
    return this->_Height;
}

bool irrlichtWindow::getDebugState()
{
    return this->_Debug;
}
