/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** serverDataReceived
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>

class ZappyGame;
class irrlichtWindow;
class guiNetworkClient;
class chessBoard;

/**
 * @struct serverMessage
 * @brief Represents a server message with a command and arguments.
 */
class serverMessage {
    public:
        std::string command; /**< The command of the server message. */
        std::vector<std::string> args; /**< The arguments of the server message. */
};

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
         * @brief Parses the server message.
         * @param message The server message to be parsed.
         * @return a server message struct made of the command and its arguments.
         */
        serverMessage parseServerMessage(std::string message);

        /**
         * @brief Gets the parent ZappyGame object.
         * @return A pointer to the parent ZappyGame object.
         */
        ZappyGame *getParentGame();

    private:
        ZappyGame *_ParentGame; /**< A pointer to the parent ZappyGame object. */
        irrlichtWindow *_ParentDevice; /**< A pointer to the parent irrlichtWindow object. */
        guiNetworkClient *_ParentClient; /**< A pointer to the parent guiNetworkClient object. */

        bool _Command_msz; /**< A boolean to check if the command msz has already been called. */
};