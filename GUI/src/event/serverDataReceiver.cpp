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
#include "chessElement/chessBoard.hpp"


ServerDataParser::ServerDataParser()
{
    this->_ParentClient = nullptr;
    this->_ParentGame = nullptr;
    this->_ParentDevice = nullptr;
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
        throw NullableParentGame();
    }
    _ParentGame = parentGame;
    if (_ParentGame->getParentDevice() == nullptr) {
        throw UnsetParentDevice();
    }
    _ParentDevice = parentGame->getParentDevice();
}

void ServerDataParser::SetParentClient(guiNetworkClient *parentClient)
{
    if (parentClient == nullptr) {
        throw NullableParentClient();
    }
    this->_ParentClient = parentClient;
}

void ServerDataParser::HandleServerMessage(std::string message)
{
    serverMessage serverMessage = parseServerMessage(message);
    if (serverMessage.command == "msz") {
        if (this->getParentGame()->getChessBoard() != nullptr && this->getParentGame()->getChessBoard()->isCreated() == false) {
            if (serverMessage.args.size() != 2) {
                std::cout << "HandleServerMessage: Warning: msz command should have 2 arguments" << std::endl;
                return;
            }
            this->getParentGame()->setPlatformWidth(std::stoi(serverMessage.args[0]));
            this->getParentGame()->setPlatformHeight(std::stoi(serverMessage.args[1]));
            std::cout << "Platform size: " << this->getParentGame()->getPlatformWidth() << "x" << this->getParentGame()->getPlatformHeight() << std::endl;
            irr::scene::ICameraSceneNode *irrActiveCam = this->getParentGame()->getParentDevice()->getActiveCamera();
            irrActiveCam->setPosition(irr::core::vector3df(-15, (this->getParentGame()->getPlatformWidth() + this->getParentGame()->getPlatformHeight()) * 3 + 25, -15));
            this->getParentGame()->getChessBoard()->createBoard();
            this->getParentGame()->getChessBoard()->InitMap(std::stoi(serverMessage.args[0]), std::stoi(serverMessage.args[1]));
        }
    } else if (serverMessage.command == "sgt") {
            this->getParentGame()->setTimeUnit(std::stoi(serverMessage.args[0]));
            std::cout << "Time unit: " << this->getParentGame()->getTimeUnit() << std::endl;
    } else if (serverMessage.command == "bct") {
        // -> commenting this because it crash each time bc the ref server doesn't send 9 args 
        // if (serverMessage.args.size() != 9) {
        //     std::cerr << "HandleServerMessage: Error: bct command should have 9 arguments" << std::endl;
        // }
        // this->getParentGame()->getChessBoard()->updateMapBtc(message);
    }
}

serverMessage ServerDataParser::parseServerMessage(std::string message)
{
    serverMessage serverMessage;

    std::istringstream iss(message);
    std::string command;
    std::vector<std::string> args;
    iss >> command;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    serverMessage.command = command;
    serverMessage.args = args;
    return serverMessage;
}

ZappyGame *ServerDataParser::getParentGame()
{
    if (_ParentGame == nullptr) {
        throw UnsetParentGame();
    }
    return _ParentGame;
}
