/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
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
     * @param argc Number of command line arguments.
     * @param argv Array of command line argument strings.
     */
    Core(int argc, char **argv);

    /**
     * @brief Initializes the Core and sets up necessary components.
     */
    void initialize();

    /**
     * @brief Runs the main loop of the game.
     */
    void run();

private:
    int m_argc; /**< Number of command line arguments. */
    char **m_argv; /**< Array of command line argument strings. */
    guiNetworkClient *m_client; /**< Pointer to the network client for GUI interaction. */
    ZappyGame *m_zappy; /**< Pointer to the main Zappy game instance. */
    irrlichtWindow m_window; /**< Instance of Irrlicht window for graphical display. */
};
