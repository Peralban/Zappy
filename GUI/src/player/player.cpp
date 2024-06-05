/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** player
*/

#include "player.hpp"
#include "game/ZappyGame.hpp"
#include "chessElement/chessPiece.hpp"
#include <iostream>

Player::Player(std::string name) :
_PlayerPosition(PlayerPos(this))
{
    this->_Level = 0;
    this->_PlayerTeam = nullptr;
    this->_chessPieceNode = nullptr;
    this->_ParentGame = nullptr;
    this->_Name = name;
    this->_PieceType = PAWN;
}

Player::Player(ZappyGame *parentGame, std::string name) :
_PlayerPosition(PlayerPos(this))
{
    this->_Level = 0;
    this->_chessPieceNode = nullptr;
    this->_ParentGame = parentGame;
    this->_Name = name;
    this->_PieceType = PAWN;
}

Player::~Player()
{
    std::cout << "\nPlayer destroyed\n" << std::endl;
}

ZappyGame *Player::getParentGame()
{
    return this->_ParentGame;
}

void Player::setParentGame(ZappyGame *parentGame)
{
    this->_ParentGame = parentGame;
    this->_PlayerPosition.initPos();
}

void Player::setName(std::string name)
{
    this->_Name = name;
}

void Player::playerInit()
{
    this->_PlayerPosition.initPos();
    chessPiece *_chessPieces = this->_ParentGame->getChessPieces();
    this-> _chessPieceNode = _chessPieces->placePiece(
        _chessPieces->getPiece(_PieceType),
        this->_PlayerPosition.getVecPosConverted(),
        this->_PlayerPosition.getVecRotConverted(),
        WHITE);
}

void Player::setTeam(Team *team)
{
    this->_PlayerTeam = team;
}

std::string Player::getName()
{
    return this->_Name;
}

PlayerPos *Player::getPlayerPosition()
{
    return &this->_PlayerPosition;
}

void Player::setPlayerPosition(PlayerPos *pos)
{
    this->_PlayerPosition = *pos;
}

void Player::updatePlayerPos()
{
    std::cout << "Player position updated" << std::endl;
    this->_chessPieceNode->setPosition(this->_PlayerPosition.getVecPosConverted());
    this->_chessPieceNode->setRotation(this->_PlayerPosition.getVecRotConverted());
}

void Player::setLevel(int level)
{
    if (level < 0)
        level = 0;
    // if (level > 8)  TOCHANGE
    //     level = 8;
    if (level > 5)
        level = 5;
    this->_Level = level;
    this->_PieceType = static_cast<pieceType>(level);
    this->updateLevel();
}

void Player::updateLevel()
{
    this->_chessPieceNode->remove();
    chessPiece *_chessPieces = this->_ParentGame->getChessPieces();
    this-> _chessPieceNode = _chessPieces->placePiece(
        _chessPieces->getPiece(_PieceType),
        this->_PlayerPosition.getVecPosConverted(),
        this->_PlayerPosition.getVecRotConverted(),
        WHITE);
}
