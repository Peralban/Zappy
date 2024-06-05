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
    this->_ParentDevice = parentDevice;
}

void ZappyGame::loadChessPieces()
{

    this->_chessPieces = new chessPiece(this->_ParentDevice);
    this->_chessPieces->loadPiece(this->_ParentDevice->getQuality());
}

chessPiece *ZappyGame::getChessPieces()
{
    return this->_chessPieces;
}

irrlichtWindow *ZappyGame::getParentDevice()
{
    return this->_ParentDevice;
}

void ZappyGame::addPlayer(std::string name)
{    
    if (this->getPlayer(name) != nullptr)
        return;
    Player *player = new Player(this, name);
    player->playerInit();
    this->_playerList.push_back(std::make_pair(name, player));
}



std::vector<std::pair<std::string, Player*>> *ZappyGame::getPlayerList()
{
    return &this->_playerList;
}

Player *ZappyGame::getPlayer(std::string name)
{
    for (auto &player : this->_playerList) {
        if (player.first == name) {
            return player.second;
        }
    }
    return nullptr;
}

