/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** guiNetworkClient
*/

#include "guiClient.hpp"

guiNetworkClient::guiNetworkClient()
{
}

guiNetworkClient::~guiNetworkClient()
{
    close(_Sockfd);
}

void guiNetworkClient::parseArgs(int ac, char **av)
{
   if (ac != 3) {
        std::cerr << "Usage: " << av[0] << " <server_ip> <server_port>" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::regex ip_regex(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})");
    if (!std::regex_match(av[1], ip_regex)) {
        std::cerr << "Invalid server IP address" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (std::stoi(av[2]) < 1024 || std::stoi(av[2]) > 65535) {
        std::cerr << "Invalid server port" << std::endl;
        exit(EXIT_FAILURE);
    }
    _ServerAdress = av[1];
    _ServerPort = std::stoi(av[2]);
}

void guiNetworkClient::createSocket()
{
    _Sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_Sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    _ServerAddr.sin_family = AF_INET;
    _ServerAddr.sin_port = htons(_ServerPort);
    if (inet_pton(AF_INET, _ServerAdress.c_str(), &_ServerAddr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }
    if (connect(_Sockfd, (struct sockaddr*)&_ServerAddr, sizeof(_ServerAddr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}

void guiNetworkClient::handleRead()
{
    std::string response = getServerResponse();
    if (response.size() > 0)
        _printServerMessage(response);
}

void guiNetworkClient::handleWrite(std::string message)
{
    send(_Sockfd, message.c_str(), message.size(), 0);
}

void guiNetworkClient::initIdentification()
{
    handleWrite("GRAPHIC\n");
    std::string response = getServerResponse();
    if (response.size() > 0) {
        if (response.find("WELCOME") != std::string::npos) {
            std::cout << "Successfully connected to server" << std::endl;
        }
    }
}

void guiNetworkClient::makeNonBlocking()
{
    int flags = fcntl(_Sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    if (fcntl(_Sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

std::string guiNetworkClient::getMapSize()
{
    handleWrite("msz\n");
    return getServerResponse();
}

std::string guiNetworkClient::getServerResponse()
{
        _Buffer[0] = '\0';
    _BytesRead = read(_Sockfd, _Buffer, sizeof(_Buffer) - 1);
    if (_BytesRead > 0) {
        _Buffer[_BytesRead] = '\0';
        return _Buffer;
    } else if (_BytesRead < 0 && errno != EWOULDBLOCK) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }
    return "";
}

int guiNetworkClient::getSocketFd()
{
    return _Sockfd;
}

void guiNetworkClient::setLinkedGame(irrlichtWindow *linkedWindow)
{
    _LinkedWindow = linkedWindow;
    _printServerMessage = std::bind(&ZappyGame::printServerMessage, linkedWindow->getLinkedZappyGame(), std::placeholders::_1);
}
