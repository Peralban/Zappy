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
    static std::vector<std::string> buffer;
    if (message == "WELCOME") {
        std::cout << "|---- WELCOME ----|" << std::endl;
        return;
    }
    if ((this->getParentGame()->getPlatformWidth() == 0 && this->getParentGame()->getPlatformHeight() == 0) && message.find("msz") == std::string::npos) {
        std::cerr << "HandleServerMessage: Error: Platform size is not setted, put args in buffer" << std::endl;
        buffer.push_back(message);
        return;
    } else if (buffer.empty() && message.find("msz") == std::string::npos) {
        for (std::string msg : buffer) {
            this->HandleServerMessage(msg);
        }
        buffer.clear();
    }
    std::cout << this->getParentGame()->getPlatformWidth() << std::endl;
    std::cout << this->getParentGame()->getPlatformHeight() << std::endl;
    serverMessage serverMessage = parseServerMessage(message);

    if (serverMessage.command == "msz") {
        if (serverMessage.args.size() != 2) {
            std::cerr << "HandleServerMessage: Error: msz command should have 2 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->setPlatformWidth(std::stoi(serverMessage.args[0]));
        this->getParentGame()->setPlatformHeight(std::stoi(serverMessage.args[1]));
        irr::scene::ICameraSceneNode *irrActiveCam = this->getParentGame()->getParentDevice()->getActiveCamera();
        irrActiveCam->setPosition(irr::core::vector3df(-15, (this->getParentGame()->getPlatformWidth() + this->getParentGame()->getPlatformHeight()) * 3 + 25, -15));
        this->getParentGame()->getChessBoard()->createBoard();
        this->getParentGame()->getChessBoard()->InitMap(std::stoi(serverMessage.args[0]), std::stoi(serverMessage.args[1]));
        std::cout << "-----------------------------------------" << std::endl;
    } else if (serverMessage.command == "sgt") {
        this->getParentGame()->setTimeUnit(std::stoi(serverMessage.args[0]));
        std::cout << "Time unit: " << this->getParentGame()->getTimeUnit() << std::endl;
    } else if (serverMessage.command == "bct") {
        if (serverMessage.args.size() != 9) {
            std::cerr << "HandleServerMessage: Error: bct command should have 9 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Updating map" << std::endl;
        this->getParentGame()->getChessBoard()->updateMapBtc(message);
        std::cout << "Map updated" << std::endl;
    } else if (serverMessage.command == "pnw") {
        if (serverMessage.args.size() != 6) {
            std::cerr << "HandleServerMessage: Error: pnw command should have 6 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->newPlayer(message);
    } else if (serverMessage.command == "ppo") {
        if (serverMessage.args.size() != 4) {
            std::cerr << "HandleServerMessage: Error: ppo command should have 4 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->updatePlayerPos(message);
    } else if (serverMessage.command == "plv") {
        if (serverMessage.args.size() != 2) {
            std::cerr << "HandleServerMessage: Error: pnw command should have 6 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->updatePlayerLevel(message);
    } else if (serverMessage.command == "pin") {
        if (serverMessage.args.size() != 10) {
            std::cerr << "HandleServerMessage: Error: ppo command should have 4 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->updatePlayerInventory(message);
    } else if (serverMessage.command == "pnw") {
        if (serverMessage.args.size() != 6) {
            std::cerr << "HandleServerMessage: Error: ppo command should have 4 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->newPlayer(message);
    } else if (serverMessage.command == "enw") {
        if (serverMessage.args.size() != 4) {
            std::cerr << "HandleServerMessage: Error: ppo command should have 4 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->newEgg(message);
    } else if (serverMessage.command == "pbc") {
        if (serverMessage.args.size() != 2) {
            std::cerr << "HandleServerMessage: Error: ppo command should have 2 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->broadcastMessage(message);
    } else if (serverMessage.command == "pdi") {
        if (serverMessage.args.size() != 1) {
            std::cerr << "HandleServerMessage: Error: ppo command should have 1 arguments" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->getParentGame()->playerDie(message);
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
    std::cout << "Command: " << command << std::endl;
    serverMessage.args = args;
    std::cout << "Args: ";
    for (std::string A : args) {
        std::cout << A << " ";
    }
    std::cout << std::endl;
    return serverMessage;
}

ZappyGame *ServerDataParser::getParentGame()
{
    if (_ParentGame == nullptr) {
        throw UnsetParentGame();
    }
    return _ParentGame;
}
