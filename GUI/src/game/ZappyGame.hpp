/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "chessElement/chessPiece.hpp"
#include "player/player.hpp"
#include <iostream>
#include <vector>

class irrlichtWindow;

/**
 * @brief The ZappyGame class represents the game logic for the Zappy game.
 * 
 * This class manages the game state, including the chess pieces, players, and time unit.
 * It provides functions to interact with the game, such as adding players, setting the time unit, and printing server messages.
 */
class ZappyGame {
    public:
        /**
         * @brief Constructs a ZappyGame object.
         */
        ZappyGame();

        /**
         * @brief Destroys the ZappyGame object.
         */
        ~ZappyGame();

        /**
         * @brief Links the ZappyGame with an irrlichtWindow object.
         * 
         * @param parentDevice The irrlichtWindow object to link with.
         */
        void linkWithDevice(irrlichtWindow *parentDevice);

        /**
         * @brief Loads every chess pieces for the game so they will be loaded only one time.
         * 
         * used for performance reasons.
         */
        void loadChessPieces();
        
        /**
         * @brief Adds a player to the game.
         * 
         * @param name The name of the player to add.
         * 
         * used when a player connects to the server or when a new player is created.
         */
        void addPlayer(std::string name);

        /**
         * @brief Sets the time unit for the game.
         * 
         * @param timeUnit The time unit to set.
         * 
         * The time unit is the number of action per second.
         */
        void setTimeUnit(int timeUnit);
        
        /**
         * @brief Gets the chess pieces of the game.
         * 
         * @return A pointer to the chess pieces object.
         */
        chessPiece *getChessPieces();

        /**
         * @brief Gets the parent irrlichtWindow object of the game.
         * 
         * @return A pointer to the parent irrlichtWindow object.
         */
        irrlichtWindow *getParentDevice();

        /**
         * @brief Gets the time unit of the game.
         * 
         * @return The time unit.
         */
        int getTimeUnit();

        /**
         * @brief Gets the list of players in the game.
         * 
         * @return A pointer to the list of players.
         */
        std::vector<std::pair<std::string, Player*>> *getPlayerList();

        /**
         * @brief Gets a player by name.
         * 
         * @param name The name of the player to get.
         * @return A pointer to the player.
         */
        Player *getPlayer(std::string name);

        /**
         * @brief Prints a server message.
         * 
         * @param message The message to print.
         * 
         * this is used to debug, the message will be printed in the console.
         */
        void printServerMessage(std::string message);

    private:
        irrlichtWindow *_ParentDevice; /**< The parent irrlichtWindow object. */

        chessPiece *_chessPieces; /**< The chess pieces Object. */
    
        std::vector<std::pair<std::string, Player*>> _playerList; /**< The list of players in the game. */

        int _TimeUnit; /**< The time unit of the game. */
};
