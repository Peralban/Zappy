/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "zappyIrrlicht/irrlichtWindow.hpp"
#include "../interface/AError.hpp"

/**
 * @class myEventReceiver
 * @brief The myEventReceiver class is responsible for handling events in the Irrlicht application.
 */
class myEventReceiver : public irr::IEventReceiver {
public:

    /**
     * @brief Constructs a myEventReceiver object.
     * @param device The pointer to the Irrlicht device.
     */
    myEventReceiver(irrlichtWindow* device);

    /**
     * @brief Destructs the myEventReceiver object.
     */
    ~myEventReceiver();

    /**
     * @brief Initializes the event receiver.
     */
    void InitEventReceiver();

    /**
     * @brief Adds a tile to the list of tiles.
     * @param tile The tile to add.
     */
    void addTile(Tile *tile);

    /**
     * @brief Adds a player to the list of players.
     * @param player The player to add.
     */
    void addPlayer(Player *player);

    /**
     * @brief Callback function that is called when an event occurs.
     * @param event The event that occurred.
     * @return True if the event was handled, false otherwise.
     */
    virtual bool OnEvent(const irr::SEvent& event);

    /**
     * @brief Handles key press events.
     * @param event The key press event.
     * @return True if the key press event was handled, false otherwise.
     */
    bool keyPress(const irr::SEvent& event);

    /**
     * @brief Handles key release events.
     * @param event The key release event.
     * @return True if the key release event was handled, false otherwise.
     */
    bool mouseClick(const irr::SEvent& event);

    /**
     * @brief Handles left mouse click events.
     * @param mouseInput The mouse input event.
     * @return True if the left mouse click event was handled, false otherwise.
     */
    bool OnLeftMouseClick(const irr::SEvent::SMouseInput& mouseInput);

    /**
     * @brief Handles right mouse click events.
     * @param mouseInput The mouse input event.
     * @return True if the right mouse click event was handled, false otherwise.
     */
    bool OnRightMouseClick(const irr::SEvent::SMouseInput& mouseInput);

    /**
     * @brief Checks if a tile is clicked.
     * @param mouseInput The mouse input event.
     * @return True if a tile is clicked, false otherwise.
     */
    bool CkeckIfTileIsClicked(const irr::SEvent::SMouseInput& mouseInput);

    /**
     * @brief Checks if a player is clicked.
     * @param mouseInput The mouse input event.
     * @return True if a player is clicked, false otherwise.
     */
    bool CheckIfSimpleNodeIsClicked(irr::core::line3d<irr::f32> ray, irr::scene::ISceneNode *node);

    /**
     * @brief Checks if a node is clicked.
     * @param ray The ray to check.
     * @param node The node to check.
     * @return True if the node is clicked, false otherwise.
     */
    bool CheckIfNodeIsClicked(irr::core::line3d<irr::f32> ray, irr::scene::IAnimatedMeshSceneNode *node);

    /**
     * @brief Get the vector of players.
     * @return The vector of players.
     */
    std::vector<Player *> getPlayers() { return _Players; }

    /**
     * @brief Removes a player from the list of players.
     *
     * This function removes a player from the game's player list using their Player object.
     * If the player does not exist in the list, no action is performed.
     *
     * @param player A pointer to the Player object of the player to remove.
     */
    void removePlayer(Player *player);

    /**
     * @brief Removes a player from the list of players by their name.
     *
     * This function removes a player from the game's player list using their name as the key.
     * If the player does not exist in the list, no action is performed.
     *
     * @param name The name of the player to remove.
     */
    void remmovePlayerByName(std::string name);

    /**
     * @brief Sets the parent window.
     * @param parentWindow The parent window to set.
     */
    irrlichtWindow *getParentWindow() { return _ParentWindow; }

    /**
     * @brief Get the debug mode.
     * @return The debug mode.
     */
    bool getDebug() { return _debug; }

    class NullableDevice : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to create myEventReceiver but given device is null".
         */
        NullableDevice() : AError("Trying to create myEventReceiver but given device is null.") {}
    };

    class UnsetDevice : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to handle an event but device is not setted".
         */
        UnsetDevice() : AError("Trying to handle an event but device is not setted.") {}
    };

    class UnsetSceneManager : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to handle an event but scene manager is not setted".
         */
        UnsetSceneManager() : AError("Trying to handle an event but scene manager is not setted.") {}
    };

    class UnsetDriver : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to handle an event but driver is not setted".
         */
        UnsetDriver() : AError("Trying to handle an event but driver is not setted.") {}
    };

    class UnsetCamera : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to handle an event but camera is not setted".
         */
        UnsetCamera() : AError("Trying to handle an event but camera is not setted.") {}
    };

    class NullTile : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to add a tile but given tile is null".
         */
        NullTile() : AError("Trying to add a tile but given tile is null.") {}
    };

    class NullPlayer : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to add a player but given player is null".
         */
        NullPlayer() : AError("Trying to add a player but given player is null.") {}
    };


private:

    bool _LeftMouseButtonDown; /**< A boolean value that indicates whether the left mouse button is down. */
    bool _RightMouseButtonDown; /**< A boolean value that indicates whether the right mouse button is down. */
    bool _debug; /**< A boolean value that indicates whether the debug mode is enabled. */

    std::vector<Tile *> _Tiles; /**< A list of Tile objects that represent the tiles of the chess board. */
    std::vector<Player *> _Players; /**< A list of Tile objects that represent the tiles of the chess board. */

    irrlichtWindow* _ParentWindow; /**< Pointer to the Irrlicht device. */
    irr::IrrlichtDevice* _Device; /**< Pointer to the Irrlicht device. */
    irr::scene::ISceneManager *_SceneManager; ///< A pointer to the irr::scene::ISceneManager object for scene management.
    irr::video::IVideoDriver *_Driver; ///< A pointer to the irr::video::IVideoDriver object for video rendering.
    irr::scene::ICameraSceneNode *_ActiveCamera; ///< A pointer to the irr::scene::ICameraSceneNode object for camera management.
};
