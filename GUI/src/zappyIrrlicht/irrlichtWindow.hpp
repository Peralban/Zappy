/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "game/ZappyGame.hpp"
#include "chessElement/chessBoard.hpp"
#include "event/irrlichtEventHandler.hpp"
#include "networkGui/guiClient.hpp"
#include "loader/objLoader.hpp"
#include "loader/textureLoader.hpp"

class guiNetworkClient;

/**
 * @class irrlichtWindow
 * @brief The irrlichtWindow class represents the main window of the GUI application.
 * It provides functions to initialize and manage the Irrlicht device, drivers, loaders,
 * chess board, event receiver, camera, and network. It also provides access to various
 * components of the GUI application.
 */
class irrlichtWindow {
public:
    /**
     * @brief Constructs an irrlichtWindow object with the specified parameters.
     * 
     * @param width The width of the window.
     * @param height The height of the window.
     * @param platformX The X position of the platform.
     * @param platformY The Y position of the platform.
     * @param tileSize The size of each tile.
     * @param driverType The type of video driver to use.
     * @param selectedQuality The selected quality settings.
     * @param debug Whether to enable debug mode.
     */
    irrlichtWindow(
        int width, int height,
        int platformX, int platformY,
        float tileSize, irr::video::E_DRIVER_TYPE driverType,
        quality selectedQuality, bool debug);

    /**
     * @brief Destroys the irrlichtWindow object.
     */
    ~irrlichtWindow();

    /**
     * @brief Creates the Irrlicht device.
     * 
     * this will call the irrlicht function irr::createDevice.
     */
    void windowCreateDevice();

    /**
     * @brief Initializes the video drivers.
     * 
     * this will get the video driver and scene manager from the irrlicht device.
     */
    void initDrivers();

    /**
     * @brief Initializes the loaders.
     * 
     * this will create the ObjLoader and TextureLoader objects.
     */
    void initLoader();

    /**
     * @brief Initializes the chess board.
     * 
     * this will create the chess board object.
     */
    void initChessBoard();

    /**
     * @brief Initializes the event receiver.
     * 
     * this will create the event receiver object.
     */
    void initEventReceiver();

    /**
     * @brief Initializes the camera.
     * 
     * this will set the camera position, rotation, target, fov and other settings.
     */
    void initCamera();

    /**
     * @brief Links the ZappyGame object to the irrlichtWindow.
     * 
     * @param ZappyGameToLink The ZappyGame object to link.
     */
    void linkZappyGame(ZappyGame *ZappyGameToLink);

    /**
     * @brief Links the guiNetworkClient object to the irrlichtWindow.
     * 
     * @param GuiClientToLink The guiNetworkClient object to link.
     */
    void linkGuiClient(guiNetworkClient *GuiClientToLink);

    /**
     * @brief Updates the network.
     * 
     * this will call the update function of the linked guiNetworkClient object.
     */
    void updateNetwork();

    /**
     * @brief Runs the window and returns the exit code.
     * 
     * @return The exit code of the window.
     */
    int runWindow();

    /**
     * @brief Returns the Irrlicht device.
     * 
     * @return The Irrlicht device.
     */
    irr::IrrlichtDevice *getDevice();

    /**
     * @brief Returns the video driver.
     * 
     * @return The video driver.
     */
    irr::video::IVideoDriver *getDriver();

    /**
     * @brief Returns the scene manager.
     * 
     * @return The scene manager.
     */
    irr::scene::ISceneManager *getSceneManager();

    /**
     * @brief Returns the selected quality settings.
     * 
     * @return The selected quality settings.
     */
    quality getQuality();

    /**
     * @brief Returns the linked ZappyGame object.
     * 
     * @return The linked ZappyGame object.
     */
    ZappyGame *getLinkedZappyGame();

    /**
     * @brief Returns the linked guiNetworkClient object.
     * 
     * @return The linked guiNetworkClient object.
     */
    guiNetworkClient *getGuiClient();

    /**
     * @brief Returns the ObjLoader object.
     * 
     * @return The ObjLoader object.
     */
    ObjLoader *getObjLoader();

    /**
     * @brief Returns the TextureLoader object.
     * 
     * @return The TextureLoader object.
     */
    TextureLoader *getTextureLoader();

    /**
     * @brief Returns the width of the window.
     * 
     * @return The width of the window.
     */
    int getWidth();

    /**
     * @brief Returns the height of the window.
     * 
     * @return The height of the window.
     */
    int getHeight();

    /**
     * @brief Returns the Width X of the platform.
     * 
     * @return The width of the platform.
     */
    int getPlatformX();

    /**
     * @brief Returns the Height Y of the platform.
     * 
     * @return The height of the platform.
     */
    int getPlatformY();

    /**
     * @brief Returns the size of each tile.
     * 
     * @return The size of each tile.
     */
    float getTileSize();

    /**
     * @brief Returns the debug state.
     * 
     * @return The debug state.
     */
    bool getDebugState();

private:
    int _Width; /** < The width of the window */
    int _Height; /** < The height of the window */
    int _PlatformX; /** < The Width X of the platform */
    int _PlatformY; /** < The Height Y of the platform */
    float _TileSize; /** < The size of each tile of the platform */

    int _socket; /** < The socket file descriptor */

    bool _Debug; /** < The debug state */

    quality _Quality; /** < The selected quality settings */
    irr::IrrlichtDevice *_Device; /** < The Irrlicht device */
    irr::video::IVideoDriver *_Driver; /** < The video driver */
    irr::scene::ISceneManager *_SceneManager; /** < The scene manager */
    irr::video::E_DRIVER_TYPE _DriverType; /** < The video driver type */
    chessBoard *_chessBoard; /** < The chess board Object */
    myEventReceiver *_EventReceiver; /** < The event receiver Object */
    ZappyGame *_LinkedZappyGame; /** < The linked ZappyGame Object */
    guiNetworkClient *_LinkedGuiClient; /** < The linked guiNetworkClient Object */

    ObjLoader *_ObjLoader; /** < The ObjLoader Object */
    TextureLoader *_TextureLoader; /** < The TextureLoader Object */
};
