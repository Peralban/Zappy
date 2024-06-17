/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** serverDataReceived
*/

#include "event/serverDataReceiver.hpp"
#include "game/ZappyGame.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"
#include "networkGui/guiClient.hpp"

ServerDataParser::ServerDataParser()
{
}

ServerDataParser::ServerDataParser(ZappyGame *parentGame)
{
    setParentGame(parentGame);
}

ServerDataParser::~ServerDataParser()
{
}

void ServerDataParser::setParentGame(ZappyGame *parentGame)
{
    if (parentGame == nullptr) {
        std::cerr << "setParentGame: Error: trying to set ParentGame but given parentGame is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    _ParentGame = parentGame;
    if (_ParentGame->getParentDevice() == nullptr) {
        std::cerr << "setParentGame: Error: ParentDevice of parentGame is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    _ParentDevice = parentGame->getParentDevice();
}

void ServerDataParser::SetParentClient(guiNetworkClient *parentClient)
{
    if (parentClient == nullptr) {
        std::cerr << "SetParentClient: Error: trying to set ParentClient but given parentClient is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_ParentClient = parentClient;
}

void ServerDataParser::HandleServerMessage(std::string message)
{
    std::cout << message << std::endl;
}

ZappyGame *ServerDataParser::getParentGame()
{
    if (_ParentGame == nullptr) {
        std::cerr << "getParentGame: Error: trying to get ParentGame but ParentGame is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return _ParentGame;
}
