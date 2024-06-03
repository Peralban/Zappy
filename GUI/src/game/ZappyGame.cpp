/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#include "game/ZappyGame.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"

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
    Player player = Player();
    player.setParentGame(this);
    player.playerInit();
    this->playerList[name] = player;

}