/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** serverDataReceived
*/

#pragma once
#include <iostream>
#include <string>

class ZappyGame;
class irrlichtWindow;
class guiNetworkClient;

/**
 * @class ServerDataParser
 * @brief Parses and handles server data messages.
 */
class ServerDataParser {
    public:
        /**
         * @brief Default constructor for ServerDataParser.
         */
        ServerDataParser();

        /**
         * @brief Constructor for ServerDataParser.
         * @param parentGame A pointer to the parent ZappyGame object.
         */
        ServerDataParser(ZappyGame *parentGame);

        /**
         * @brief Destructor for ServerDataParser.
         */
        ~ServerDataParser();

        /**
         * @brief Sets the parent ZappyGame object.
         * @param parentGame A pointer to the parent ZappyGame object.
         */
        void setParentGame(ZappyGame *parentGame);

        /**
         * @brief Handles the server message.
         * @param message The server message to be handled.
         */
        void HandleServerMessage(std::string message);

        /**
         * @brief Sets the parent guiNetworkClient object.
         * @param parentClient A pointer to the parent guiNetworkClient object.
         */
        void SetParentClient(guiNetworkClient *parentClient);

        /**
         * @brief Gets the parent ZappyGame object.
         * @return A pointer to the parent ZappyGame object.
         */
        ZappyGame *getParentGame();

    private:
        ZappyGame *_ParentGame; /**< A pointer to the parent ZappyGame object. */
        irrlichtWindow *_ParentDevice; /**< A pointer to the parent irrlichtWindow object. */
        guiNetworkClient *_ParentClient; /**< A pointer to the parent guiNetworkClient object. */
};