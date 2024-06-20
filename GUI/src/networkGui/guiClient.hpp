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
     * 
     * basically consist of handleWrite("GRAPHIC\n");
     */
    void initIdentification();

    /**
     * @brief Asks the server for the initial data for example the map size.
     */
    void askInitData();

    /**
     * @brief Selects the socket for reading.
     * 
     * if the socket is ready to read, it will call handleRead.
     */
    void selectSocket();

    /**
     * @brief Retrieves the bytes available to read.
     * @return The server data as a string.
     */
    std::string getServerData();

    /**
     * @brief Retrieves all of the bytes read from the server as a string.
     * @return The server response as a string.
     */
    std::string getServerResponse();

    /**
     * @brief Retrieves the socket file descriptor.
     * @return The socket file descriptor.
     */
    int getSocketFd();

    /**
     * @brief Retrieves the server address.
     * @return The server address.
     */
    struct sockaddr_in getServerAddr();

private:
    std::string _ServerAdress; // The server address
    int _ServerPort; // The server port

    std::string _ServData; // The data read from the server

    int _Sockfd; // The socket file descriptor
    struct sockaddr_in _ServerAddr; // The server address structure
    irrlichtWindow *_LinkedWindow; // The linked irrlichtWindow object
    ZappyGame *_LinkedGame; // The linked ZappyGame object
    ServerDataParser *_ServerDataParser; // The server data parser object

    std::function<void(std::string)> _HandleServerMessage; // A pointer to a function in the ZappyGame class
};