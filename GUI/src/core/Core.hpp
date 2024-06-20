/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** Core
*/
#pragma once

#include "zappyIrrlicht/irrlichtWindow.hpp"
#include "networkGui/guiClient.hpp"
#include "game/ZappyGame.hpp"

/**
 * @brief The Core class manages the initialization and running of the Zappy game.
 */
class Core {
public:
    /**
     * @brief Constructor for Core.
     * 
     * Initializes the Core with the specified dimensions and settings.
     * 
     * @param width Width of the window.
     * @param height Height of the window.
     * @param platformX X dimension of the game platform.
     * @param platformY Y dimension of the game platform.
     * @param tileSize Size of the game tiles.
     * @param gameQuality Quality setting for the game.
     * @param debug Whether to enable debug mode.
     */
    Core(int width, int height, int platformX, int platformY, float tileSize, quality gameQuality, bool debug);

    /**
     * @brief Destructor for Core.
     * 
     * Cleans up resources allocated by Core.
     */
    ~Core();

    /**
     * @brief Initializes the Core and sets up necessary components.
     * 
     * @param ac Number of command line arguments.
     * @param av Array of command line argument strings.
     */
    void initialize(int ac, char **av);

    /**
     * @brief Runs the main loop of the game.
     */
    void run();

private:
    irrlichtWindow m_window; /**< Instance of Irrlicht window for graphical display. */
    guiNetworkClient *m_client; /**< Pointer to the network client for GUI interaction. */
    ZappyGame *m_zappy; /**< Pointer to the main Zappy game instance. */
};
