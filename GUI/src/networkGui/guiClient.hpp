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


class guiNetworkClient {
public:
    guiNetworkClient();
    ~guiNetworkClient();

    void setLinkedGame(irrlichtWindow *linkedWindow);
    void parseArgs(int ac, char **av);
    void createSocket();

    void handleRead();
    void handleWrite(std::string message);

    void makeNonBlocking();

    void initIdentification();

    std::string getServerResponse();
    std::string getMapSize();
    std::string getTimeUnit();
    int getSocketFd();

private:
    std::string _ServerAdress;
    int _ServerPort;

    char _Buffer[8192];
    int _BytesRead;

    int _Sockfd;
    struct sockaddr_in _ServerAddr;
    irrlichtWindow *_LinkedWindow;
    ZappyGame *_LinkedGame;

    //create a pointer to a function in the zappyGame class
    std::function<void(std::string)> _printServerMessage;

};