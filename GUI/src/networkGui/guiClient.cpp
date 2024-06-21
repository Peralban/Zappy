/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** guiNetworkClient
*/

#include "guiClient.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"
#include "../event/serverDataReceiver.hpp"

guiNetworkClient::guiNetworkClient()
    : _ServerDataParser(nullptr), _HandleServerMessage(nullptr) {}

guiNetworkClient::guiNetworkClient(irrlichtWindow *linkedWindow)
    : _ServerDataParser(nullptr), _HandleServerMessage(nullptr) {
    setLinkedGame(linkedWindow);
    _ServerDataParser = new ServerDataParser();
    _ServerDataParser->setParentGame(_LinkedGame);
    _ServerDataParser->SetParentClient(this);
    _HandleServerMessage = std::bind(&ServerDataParser::HandleServerMessage, _ServerDataParser, std::placeholders::_1);
}

guiNetworkClient::~guiNetworkClient()
{
    close(_Sockfd);
}

void guiNetworkClient::createSocket()
{
    _Sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_Sockfd < 0) {
        std::cerr << "createSocket: Error: socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "--------------------- Socket created ---------------------" << std::endl;

    _ServerAddr.sin_family = AF_INET;
    _ServerAddr.sin_port = htons(_ServerPort);
    std::cout << "--------------------- Connecting to " << _ServerAdress << ":" << _ServerPort << " ---------------------" << std::endl;
    if (inet_pton(AF_INET, _ServerAdress.c_str(), &_ServerAddr.sin_addr) <= 0) {
        std::cerr << "createSocket: Error: Invalid address/ Address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (connect(_Sockfd, (struct sockaddr*)&_ServerAddr, sizeof(_ServerAddr)) < 0) {
        perror("createSocket: Error: Connection failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "--------------------- Successfully connected to " << _ServerAdress << ":" << _ServerPort << " ---------------------" << std::endl;
}

void guiNetworkClient::handleRead()
{
    std::string response = getServerResponse();
    if (response.size() > 0)
        _HandleServerMessage(response);
}

void guiNetworkClient::handleWrite(std::string message)
{
    send(_Sockfd, message.c_str(), message.size(), 0);
}

void guiNetworkClient::initIdentification()
{
    handleWrite("GRAPHIC\n");
    std::string response = getServerResponse();
    if (response.size() > 0 && response.find("WELCOME") != std::string::npos)
        std::cout << "------- Successfully registered as GRAPHIC -----------"<< std::endl;
}

void guiNetworkClient::askInitData()
{
    initIdentification();

    handleWrite("msz\n");
    _HandleServerMessage(getServerResponse());
    handleWrite("sgt\n");
    _HandleServerMessage(getServerResponse());
    handleWrite("mct\n");
    _HandleServerMessage(getServerResponse());
}

void guiNetworkClient::makeNonBlocking()
{
    int flags = fcntl(_Sockfd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "makeNonBlocking: Error: failed to get socket flags" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (fcntl(_Sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "makeNonBlocking: Error: failed to set socket to non-blocking" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket is now non-blocking" << std::endl;
}

void guiNetworkClient::selectSocket()
{
    fd_set readFds;
    struct timeval timeOut;
    FD_ZERO(&readFds);
    FD_SET(_Sockfd, &readFds);
    timeOut.tv_sec = 0;
    timeOut.tv_usec = 0;

    int selectResult = select(_Sockfd + 1, &readFds, NULL, NULL, &timeOut);
    if (selectResult < 0) { 
        std::cerr << "selectSocket: Error: select failed" << std::endl;
        exit(EXIT_FAILURE);
    } else if (selectResult > 0) {
        if (FD_ISSET(_Sockfd, &readFds)) {
            char buffer[1024];
            int bytesRead = recv(_Sockfd, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) {
                if (bytesRead == 0) {
                    std::cerr << "Connection closed by peer." << std::endl;
                } else {
                    std::cerr << "recv error: " << strerror(errno) << std::endl;
                }
                exit(EXIT_FAILURE);
            } else {
                buffer[bytesRead] = '\0';
                _HandleServerMessage(buffer);
            }
        }
    }
}

std::string guiNetworkClient::getServerResponse()
{
    std::string response = getServerData();
    if (response.size() > 0) {
        _ServData.append(response);
    }
    if (response == "\n") {
        std::string data = _ServData;
        _ServData.clear();
        std::cout << "Server response: " << data << std::endl;
        return data;
    }
    return getServerResponse();
}

std::string guiNetworkClient::getServerData()
{
    char Buffer[2] = {0};
    std::string message = "";

    if (recv(this->_Sockfd, Buffer, 1, 0) < 0)
        return "";
    message = std::string(Buffer);
    return message;
}

int guiNetworkClient::getSocketFd()
{
    if (_Sockfd < 0) {
        std::cerr << "getSocketFd: Error: socket file descriptor not initialized" << std::endl;
        exit(EXIT_FAILURE);
    }
    return _Sockfd;
}

struct sockaddr_in guiNetworkClient::getServerAddr()
{
    if (_ServerAddr.sin_port == 0) {
        std::cerr << "getServerAddr: Error: server address not initialized" << std::endl;
        exit(EXIT_FAILURE);
    }
    return _ServerAddr;
}

void guiNetworkClient::setLinkedGame(irrlichtWindow *linkedWindow)
{
    if (!linkedWindow) {
        std::cerr << "Error: irrlichtWindow not linked" << std::endl;
        exit(EXIT_FAILURE);
    }
    _ServerAdress = linkedWindow->getServerAdress();
    _ServerPort = linkedWindow->getServerPort();
    _LinkedWindow = linkedWindow;
    if (!linkedWindow->getLinkedZappyGame()) {
        std::cerr << "setLinkedGame Error: linked window is not linked to a game" << std::endl;
        exit(EXIT_FAILURE);
    }
     if (!linkedWindow->getLinkedZappyGame()->getServerDataParser()) {
        std::cerr << "setLinkedGame Error: linked window linked game is not linked to a server data parser" << std::endl;
        exit(EXIT_FAILURE);
    }
    _ServerDataParser = linkedWindow->getLinkedZappyGame()->getServerDataParser();
    _HandleServerMessage = std::bind(&ServerDataParser::HandleServerMessage, linkedWindow->getLinkedZappyGame()->getServerDataParser(), std::placeholders::_1);
}
