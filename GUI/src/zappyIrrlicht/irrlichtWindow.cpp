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
    if (ac != 5) {
        throw WrongArgs();
    }
    if (std::string(av[1]) == "-p") {
        this->_ServerPort = std::stoi(av[2]);
    } else if (std::string(av[1]) == "-h") {
        this->_ServerAdress = av[2];
    } else {
        throw WrongArgs();
    }
    if (std::string(av[3]) == "-p") {
        this->_ServerPort = std::stoi(av[4]);
    } else if (std::string(av[3]) == "-h") {
        this->_ServerAdress = av[4];
    } else {
        throw WrongArgs();
    }
}

void irrlichtWindow::windowCreateDevice()
{
    irr::IrrlichtDevice *device = irr::createDevice(this->_DriverType, irr::core::dimension2d<irr::u32>(this->_Width, this->_Height), 16, false, false, false, 0);
	if (device == 0) {
        throw NotDeviceCreated();
    }
	this->_Device = device;
}

void irrlichtWindow::initDrivers()
{
    if (!this->_Device) {
        throw DeviceUninitialized();
    }
    this->_Driver = this->_Device->getVideoDriver();
    this->_SceneManager = this->_Device->getSceneManager();
    this->_GuiEnv = this->_Device->getGUIEnvironment();
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
    float rotatespeed = 40.0f;
    float movespeed = 0.35f;
    bool novertical = false;
    irr::SKeyMap *keyMap = new irr::SKeyMap[6];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_KEY_Z;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = irr::KEY_KEY_D;
    keyMap[4].Action = irr::EKA_JUMP_UP;
    keyMap[4].KeyCode = irr::KEY_SPACE;
    keyMap[5].Action = irr::EKA_CROUCH;
    keyMap[5].KeyCode = irr::KEY_LSHIFT;

	this->_ActiveCamera = this->_SceneManager->addCameraSceneNodeFPS(0, rotatespeed, movespeed, -1, keyMap, 6, novertical, 0.5f, false, true);
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

void irrlichtWindow::LinkEventReceiver(guiNetworkClient* client)
{
    this->_EventReceiver = new myEventReceiver(this);
    if (this->_EventReceiver == nullptr) {
        throw UnableToCreateEvent();
    }
    this->_Device->setEventReceiver(this->_EventReceiver);
    this->_EventReceiver->InitEventReceiver(client);
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

void signalHandler(int signal) {
    gSignalStatus = signal;
}

static void UpdateAllPlayers(ZappyGame *game, guiNetworkClient *client)
{

    if (game->getPlayerList()->empty())
        return;
    for (auto player : *game->getPlayerList()) {
        std::string player_name = player.second->getName();
        if (game->getPlayer(player_name) == nullptr) {
            UpdateAllPlayers(game, client);
            break;
        }
        client->handleWrite("ppo " + player.second->getName() + "\n");
        client->selectSocket();
        if (game->getPlayer(player_name) == nullptr) {
            UpdateAllPlayers(game, client);
            break;
        }
        client->handleWrite("plv " + player.second->getName() + "\n");
        client->selectSocket();
        if (game->getPlayer(player_name) == nullptr) {
            UpdateAllPlayers(game, client);
            break;
        }
        client->handleWrite("pin " + player.second->getName() + "\n");
        client->selectSocket();
    }
}

int irrlichtWindow::runWindow(ZappyGame *game, guiNetworkClient *client)
{
    bool isRunning = true;

    try {
        client->handleWrite("GRAPHIC\n");
        client->getServerResponse();
        client->handleRead();
        client->makeNonBlocking();
        client->handleWrite("msz\n");
        client->selectSocket();
        client->handleWrite("mct\n");
        client->selectSocket();
        client->handleWrite("sgt\n");
        client->selectSocket();
        std::cout << "Running window..." << std::endl;
        while(this->_Device->run() && isRunning) {
            std::signal(SIGINT, signalHandler);
            if (gSignalStatus == SIGINT) {
                isRunning = false;
                client->handleWrite("quit\n");
                if (_EventReceiver) {
                    delete _EventReceiver;
                }
                if (_ObjLoader) {
                    delete _ObjLoader;
                }
                if (_TextureLoader) {
                    delete _TextureLoader;
                }
                if (_Device) {
                    _Device->drop();
                }
                if (isRunning == false)
                    return 0;
            }
            for (int i = 0; i < game->getTimeUnit(); i++) {
                this->_LinkedGuiClient->selectSocket();
            }
            UpdateAllPlayers(game, client);
            if (this->_Device->isWindowActive() && (game->getPlatformWidth() != 0 && game->getPlatformHeight() != 0)) {
                this->_LinkedZappyGame->getChessBoard()->updateMapItem();
                this->_Driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
                this->_SceneManager->drawAll();
                this->_GuiEnv->drawAll(); // Draw the GUI
                this->drawCursor();
                this->_Driver->endScene();
            } else {
                this->_Device->yield();
            }
        }
    } catch (const std::exception &e) {
        exit(0);
    };
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
        throw UninitializedTextureLoader();
    }
    return this->_TextureLoader;
}

myEventReceiver *irrlichtWindow::getEventReceiver()
{
    if (!this->_EventReceiver) {
        throw UninitializedEventReceiver();
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

irrlichtWindow::~irrlichtWindow()
{
    if (_EventReceiver) {
        delete _EventReceiver;
    }
    if (_ObjLoader) {
        delete _ObjLoader;
    }
    if (_TextureLoader) {
        delete _TextureLoader;
    }
    if (_Device) {
        _Device->drop();
    }
}

irr::gui::IGUIEnvironment *irrlichtWindow::getGuiEnv()
{
    if (!this->_GuiEnv) {
        throw GuiEnvUninitialized();
    }
    return this->_GuiEnv;
}