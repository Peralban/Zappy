/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#include "ZappyGame.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include "../player/player.hpp"

ZappyGame::ZappyGame()
{
    this->_chessPieces = nullptr;
    this->_ParentDevice = nullptr;
}

ZappyGame::~ZappyGame()
{
}

void ZappyGame::linkWithDevice(irrlichtWindow *parentDevice)
{
    if (parentDevice == nullptr) {
        std::cerr << "trying to link with device but given parentDevice is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_ParentDevice = parentDevice;
}

void ZappyGame::setServerDataParser(ServerDataParser *serverDataParser)
{
    if (serverDataParser == nullptr) {
        std::cerr << "trying to set ServerDataParser but given serverDataParser is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_serverDataParser = serverDataParser;
}

void ZappyGame::loadChessPieces()
{
    this->_chessPieces = new chessPiece(this->_ParentDevice);
    if (this->_chessPieces == nullptr) {
        std::cerr << "loadChessPieces: Error: Couldn't create chessPieces" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (this->_ParentDevice == nullptr) {
        std::cerr << "loadChessPieces: Error: ParentDevice is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_chessPieces->loadPiece(this->_ParentDevice->getQuality());
}

void ZappyGame::initServerEvents()
{
    this->_serverDataParser = new ServerDataParser(this);
}

chessPiece *ZappyGame::getChessPieces()
{
    if (this->_chessPieces == nullptr)
        this->loadChessPieces();
    return this->_chessPieces;
}

irrlichtWindow *ZappyGame::getParentDevice()
{
    if (this->_ParentDevice == nullptr) {
        std::cerr << "getParentDevice: Error: ParentDevice is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_ParentDevice;
}

int ZappyGame::getTimeUnit()
{
    if (this->_TimeUnit == 0) {
        std::cout << "getTimeUnit: Warning: TimeUnit is not setted returning default 100" << std::endl;
        return 100;
    }
    return this->_TimeUnit;
}

void ZappyGame::addPlayer(std::string name)
{    
    if (this->getPlayer(name) != nullptr)
        return;
    Player *player = new Player(this, name);
    if (player == nullptr) {
        std::cerr << "addPlayer: Error: Couldn't create player" << std::endl;
        exit(EXIT_FAILURE);
    }
    player->playerInit();
    this->_playerList.push_back(std::make_pair(name, player));
}

void ZappyGame::setTimeUnit(int timeUnit)
{
    this->_TimeUnit = timeUnit;
}

std::vector<std::pair<std::string, Player*>> *ZappyGame::getPlayerList()
{
    if (this->_playerList.empty())
        std::cout << "getPlayerList: WARNING : PlayerList is empty" << std::endl;
    return &this->_playerList;
}

Player *ZappyGame::getPlayer(std::string name)
{
    if (this->_playerList.empty()) {
        std::cout << "getPlayer: WARNING : PlayerList is empty but trying to get a player by name" << std::endl;
        return nullptr;
    }
    for (auto &player : this->_playerList) {
        if (player.first == name) {
            return player.second;
        }
    }
    return nullptr;
}

ServerDataParser *ZappyGame::getServerDataParser()
{
    if (this->_serverDataParser == nullptr) {
        std::cerr << "getServerDataParser: Error: ServerDataParser is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_serverDataParser;
}
