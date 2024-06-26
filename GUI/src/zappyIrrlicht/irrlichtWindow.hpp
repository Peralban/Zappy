/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "game/ZappyGame.hpp"
#include "event/irrlichtEventHandler.hpp"
#include "event/serverDataReceiver.hpp"
#include "networkGui/guiClient.hpp"
#include "loader/objLoader.hpp"
#include "loader/textureLoader.hpp"
#include "../interface/AError.hpp"
#include <csignal>

class guiNetworkClient;
class myEventReceiver;

namespace
{
    volatile std::sig_atomic_t gSignalStatus;
}

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
     * @param driverType The type of video driver to use.
     * @param selectedQuality The selected quality settings.
     * @param debug Whether to enable debug mode.
     */
    irrlichtWindow(
        int width, int height,
        irr::video::E_DRIVER_TYPE driverType,
        quality selectedQuality, bool debug);

    /**
     * @brief Destroys the irrlichtWindow object.
     */
    ~irrlichtWindow();

    /**
     * @brief Parses the command line arguments.
     * @param ac The number of command line arguments.
     * @param av An array of command line arguments.
     * 
     * this will use the command line arguments to set the server address and port.
     * like this: ./zappy_gui adress port
     */
    void parseArgs(int ac, char **av);

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
     * @brief Initializes the event receiver.
     * 
     * this will create the event receiver object.
     */
    void LinkEventReceiver(guiNetworkClient* client);

    /**
     * @brief Initializes the camera.
     * 
     * this will set the camera position, rotation, target, fov and other settings.
     */
    void initCamera();

    /**
     * @brief Initializes the cursor with a length and RGB color.
     * 
     * this will set the cursor length and color.
     */
    void initCursor(int length, int thickness, int R, int G, int B);

    /**
     * @brief Initializes the cursor with a irr::video::SColor.
     * 
     * this will set the cursor length and color.
     */
    void initCursor(int length, int thickness, irr::video::SColor color);

    /**
     * @brief set the cursor length.
     * 
     * this will set or change the cursor length.
     */
    void setCursorLength(int length);

    /**
     * @brief set the cursor thickness.
     * 
     * this will set or change the cursor thickness.
     */
    void setCursorThickness(int thickness);

    /**
     * @brief Creates the cursor.
     * 
     * this will create the cursor object.
     */
    void drawCursor();

    void createText();

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
     * @brief Returns the server address.
     * 
     * @return The server address.
     * 
     * the server adress should be av[1] from the command line arguments.
     */
    char *getServerAdress();

    /**
     * @brief Returns the server port.
     * 
     * @return The server port.
     * 
     * the server port should be av[2] from the command line arguments.
     */
    int getServerPort();

    /**
     * @brief Runs the window and returns the exit code.
     *
     * @param game The ZappyGame object.
     * @param client The guiNetworkClient object.
     * @return The exit code of the window.
     */
    int runWindow(ZappyGame *game, guiNetworkClient *client);

    /**
     * @brief Returns the active camera.
     * 
     * @return The active camera.
     */
    irr::scene::ICameraSceneNode *getActiveCamera();

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
     * @brief Returns the event receiver object.
     * 
     * @return The event receiver object.
     */
    myEventReceiver *getEventReceiver();

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
     * @brief Returns the debug state.
     * 
     * @return The debug state.
     */
    bool getDebugState();

    irr::gui::IGUIEnvironment *getGuiEnv();

    class WrongArgs : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Usage: ./zappy_gui <server_ip> <server_port>.".
         */
        WrongArgs() : AError("Usage: ./zappy_gui <server_ip> <server_port>.") {}
    };

    class InvalidIP : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Invalid server IP address.".
         */
        InvalidIP() : AError("Invalid server IP address.") {}
    };

    class InvalidPort : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Invalid server port.".
         */
        InvalidPort() : AError("Invalid server port.") {}
    };

    class NotDeviceCreated : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Could not create device.".
         */
        NotDeviceCreated() : AError("Could not create device.") {}
    };


    class DeviceUninitialized : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Device not initialized, can't create driver.".
         */
        DeviceUninitialized() : AError("Device not initialized, can't create driver.") {}
    };

    class UnableToCreateEvent : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Could not create event receiver.".
         */
        UnableToCreateEvent() : AError("Could not create event receiver.") {}
    };

    class UninitializedServerAdress : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Server adress not initialized.".
         */
        UninitializedServerAdress() : AError("Server adress not initialized.") {}
    };

    class UninitializedCamera : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Camera not initialized.".
         */
        UninitializedCamera() : AError("Camera not initialized.") {}
    };

    class DeviceUnitialized : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Device not initialized.".
         */
        DeviceUnitialized() : AError("Device not initialized") {}
    };

    class DriverUnitialized : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Driver not initialized.".
         */
        DriverUnitialized() : AError("Driver not initialized") {}
    };

    class SceneManagerUnitialized : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "SceneManager not initialized.".
         */
        SceneManagerUnitialized() : AError("SceneManager not initialized") {}
    };

    class UnlinkedZappyGame : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "ZappyGame not linked.".
         */
        UnlinkedZappyGame() : AError("ZappyGame not linked.") {}
    };

    class UnlinkedGuiNetworkClient : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "guiNetworkClient not linked.".
         */
        UnlinkedGuiNetworkClient() : AError("guiNetworkClient not linked.") {}
    };


    class UninitializedGuiNetworkClient : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "guiNetworkClient not initialized.".
         */
        UninitializedGuiNetworkClient() : AError("guiNetworkClient not initialized.") {}
    };

    class SelectError : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Select error".
         */
        SelectError() : AError("Select error") {}
    };

    class UninitializedObjLoader : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Obj loader not initialized.".
         */
        UninitializedObjLoader() : AError("Obj loader not initialized.") {}
    };

    class UninitializedTextureLoader : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Texture loader not initialized.".
         */
        UninitializedTextureLoader() : AError("Texture loader not initialized.") {}
    };

    class UnlinkedServerDataParser : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "ServerDataParser not linked.".
         */
        UnlinkedServerDataParser() : AError("ServerDataParser not linked.") {}
    };

    class UninitializedZappyGame : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "ZappyGame not initialized.".
         */
        UninitializedZappyGame() : AError("ZappyGame not initialized.") {}
    };

    class UnableToCreateCamera : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Could not create camera.".
         */
        UnableToCreateCamera() : AError("Could not create camera.") {}
    };

    class UninitializedEventReceiver : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Event receiver not initialized.".
         */
        UninitializedEventReceiver() : AError("Event receiver not initialized.") {}
    };

    class GuiEnvUninitialized : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "GUI environment not initialized.".
         */
        GuiEnvUninitialized() : AError("GUI environment not initialized.") {}
    };

private:
    int _Width; /** < The width of the window */
    int _Height; /** < The height of the window */

    int _CursorLength; /** < The cursor length */
    int _CursorThickness; /** < The cursor thickness */
    irr::video::SColor _CursorColor; /** < The cursor color */

    char *_ServerAdress; /** < The server address under the form : 255.255.255.255 */
    int _ServerPort; /** < The server port */

    bool _Debug; /** < The debug state */

    quality _Quality; /** < The selected quality settings */

    irr::IrrlichtDevice *_Device; /** < The Irrlicht device */
    irr::video::IVideoDriver *_Driver; /** < The video driver */
    irr::scene::ISceneManager *_SceneManager; /** < The scene manager */
    irr::video::E_DRIVER_TYPE _DriverType; /** < The video driver type */
    irr::scene::ICameraSceneNode *_ActiveCamera; /** < The camera */
    irr::gui::IGUIEnvironment *_GuiEnv; /** < The GUI environment */

    myEventReceiver *_EventReceiver; /** < The event receiver Object */
    ZappyGame *_LinkedZappyGame; /** < The linked ZappyGame Object */
    guiNetworkClient *_LinkedGuiClient; /** < The linked guiNetworkClient Object */

    ObjLoader *_ObjLoader; /** < The ObjLoader Object */
    TextureLoader *_TextureLoader; /** < The TextureLoader Object */
};
