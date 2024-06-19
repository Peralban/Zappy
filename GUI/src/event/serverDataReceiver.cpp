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
    this->_Command_msz= false;
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
    serverMessage serverMessage = parseServerMessage(message);

    if (serverMessage.command == "msz" && !_Command_msz) {
        if (serverMessage.args.size() != 2) {
            std::cerr << "HandleServerMessage: Error: msz command should have 2 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->setPlatformWidth(std::stoi(serverMessage.args[0]));
        this->getParentGame()->setPlatformHeight(std::stoi(serverMessage.args[1]));
        std::cout << "Platform size: " << this->getParentGame()->getPlatformWidth() << "x" << this->getParentGame()->getPlatformHeight() << std::endl;
        irr::scene::ICameraSceneNode *irrActiveCam = this->getParentGame()->getParentDevice()->getActiveCamera();
        irrActiveCam->setPosition(irr::core::vector3df(-15, (this->getParentGame()->getPlatformWidth() + this->getParentGame()->getPlatformHeight()) * 3 + 25, -15));
        this->getParentGame()->getChessBoard()->createBoard();
        this->_Command_msz = true;
        this->getParentGame()->getChessBoard()->InitMap(std::stoi(serverMessage.args[0]), std::stoi(serverMessage.args[1]));
    } else if (serverMessage.command == "sgt") {
            this->getParentGame()->setTimeUnit(std::stoi(serverMessage.args[0]));
            std::cout << "Time unit: " << this->getParentGame()->getTimeUnit() << std::endl;
    } else if (serverMessage.command == "bct") {
        if (serverMessage.args.size() != 9) {
            std::cerr << "HandleServerMessage: Error: bct command should have 9 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->getChessBoard()->updateMapBtc(message);
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
        std::cerr << "getParentGame: Error: trying to get ParentGame but ParentGame is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return _ParentGame;
}
