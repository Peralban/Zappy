/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** guiNetworkClient
*/

#pragma once

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex>
#include <functional>
#include "zappyIrrlicht/irrlichtWindow.hpp"

/**
 * @class guiNetworkClient
 * @brief The guiNetworkClient class represents the network client for the GUI.
*/
class guiNetworkClient {
public:
    /**
     * @brief Constructs a guiNetworkClient object.
     */
    guiNetworkClient();

    /**
     * @brief Constructs a guiNetworkClient object.
     * @param linkedWindow A pointer to the irrlichtWindow object.
     */
    guiNetworkClient(irrlichtWindow *linkedWindow);

    /**
     * @brief Destroys the guiNetworkClient object.
     */
    ~guiNetworkClient();

    /**
     * @brief Sets the linked irrlichtWindow object.
     * @param linkedWindow A pointer to the irrlichtWindow object.
     */
    void setLinkedGame(irrlichtWindow *linkedWindow);

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
     * @brief Creates a socket for network communication.
     */
    void createSocket();

    /**
     * @brief Handles the read operation on the socket.
     */
    void handleRead();

    /**
     * @brief Handles the write operation on the socket.
     * @param message The message to be sent.
     */
    void handleWrite(std::string message);

    /**
     * @brief Makes the socket non-blocking.
     */
    void makeNonBlocking();

    /**
     * @brief send a message to the server saying that we are a GUI.
     */
    void initIdentification();

    /**
     * @brief Retrieves the server response.
     * @return The server response as a string.
     * 
     * this is used with a blocking socket to get the server response.
     */
    std::string getServerResponse();

    /**
     * @brief Retrieves the map size.
     * @return The map size as a string.
     */
    std::string getMapSize();

    /**
     * @brief Retrieves the time unit.
     * @return The time unit as a string.
     */
    std::string getTimeUnit();

    /**
     * @brief Retrieves the socket file descriptor.
     * @return The socket file descriptor.
     */
    int getSocketFd();

private:
    std::string _ServerAdress; // The server address
    int _ServerPort; // The server port

    char _Buffer[8192]; // The buffer for reading data
    int _BytesRead; // The number of bytes read

    int _Sockfd; // The socket file descriptor
    struct sockaddr_in _ServerAddr; // The server address structure
    irrlichtWindow *_LinkedWindow; // The linked irrlichtWindow object
    ZappyGame *_LinkedGame; // The linked ZappyGame object

    std::function<void(std::string)> _printServerMessage; // A pointer to a function in the ZappyGame class
};