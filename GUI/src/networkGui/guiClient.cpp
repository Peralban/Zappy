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
        throw SocketFailed();
    }
    std::cout << "--------------------- Socket created ---------------------" << std::endl;

    _ServerAddr.sin_family = AF_INET;
    _ServerAddr.sin_port = htons(_ServerPort);
    std::cout << "--------------------- Connecting to " << _ServerAdress << ":" << _ServerPort << " ---------------------" << std::endl;
    if (inet_pton(AF_INET, _ServerAdress.c_str(), &_ServerAddr.sin_addr) <= 0) {
        throw InvalidAdress();
    }
    if (connect(_Sockfd, (struct sockaddr*)&_ServerAddr, sizeof(_ServerAddr)) < 0) {
        throw ConnectionFailed();
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

void guiNetworkClient::makeNonBlocking()
{
    int flags = fcntl(_Sockfd, F_GETFL, 0);
    if (flags == -1) {
        throw FcntlException();
    }
    if (fcntl(_Sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw FcntlException();
    }
    std::cout << "Socket is now non-blocking" << std::endl;
}

std::string readUntilNewline(int sockfd) {
    char buffer[1];
    std::string result;

    while (true) {
        int bytesRead = recv(sockfd, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            // Handle error or connection closed by peer
            break;
        }
        result += buffer[0];
        if (buffer[0] == '\n') {
            break;
        }
    }
    return result;
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
        throw SelectError();
    } else if (selectResult > 0) {
        if (FD_ISSET(_Sockfd, &readFds)) {
            std::string buffer = readUntilNewline(_Sockfd);
            if (buffer.empty()) {
                if (errno == EWOULDBLOCK)
                    std::cerr << "Connection closed by peer." << std::endl;
                else
                    std::cerr << "recv error: " << strerror(errno) << std::endl;
                }
                throw SelectError();
            } else {
                buffer.pop_back();
                std::cout << "MESSAGES: " << buffer << std::endl;
                _HandleServerMessage(buffer);
            }
        } else
            std::cerr << "selectSocket: Error: socket not set in readFds" << std::endl;
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
        throw UninitializedSocketFileDescriptor();
    }
    return _Sockfd;
}

struct sockaddr_in guiNetworkClient::getServerAddr()
{
    if (_ServerAddr.sin_port == 0) {
        throw ServerAdressUninitialized();
    }
    return _ServerAddr;
}

void guiNetworkClient::setLinkedGame(irrlichtWindow *linkedWindow)
{
    if (!linkedWindow) {
        throw IrrlichtWindowNotLinked();
    }
    _ServerAdress = linkedWindow->getServerAdress();
    _ServerPort = linkedWindow->getServerPort();
    _LinkedWindow = linkedWindow;
    if (!linkedWindow->getLinkedZappyGame()) {
        throw GameUnlinkToWindow();
    }
     if (!linkedWindow->getLinkedZappyGame()->getServerDataParser()) {
        throw GameUnlinkToDataParser();
    }
    _ServerDataParser = linkedWindow->getLinkedZappyGame()->getServerDataParser();
    _HandleServerMessage = std::bind(&ServerDataParser::HandleServerMessage, linkedWindow->getLinkedZappyGame()->getServerDataParser(), std::placeholders::_1);
}
