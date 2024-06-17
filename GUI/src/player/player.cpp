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
    if (this->_ParentGame == nullptr) {
        std::cerr << "getParentGame: Error: ParentGame is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_ParentGame;
}

void Player::setParentGame(ZappyGame *parentGame)
{
    if (parentGame == nullptr) {
        std::cerr << "setParentGame: Error: trying to set ParentGame but given parentGame is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_ParentGame = parentGame;
    this->_PlayerPosition.initPos();
}

void Player::setName(std::string name)
{
    if (name == "undefined") {
        std::cout << "setName: Warning: Player name is undefined, name is not setted" << std::endl;
        return;
    }
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
        WHITE
    );
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
    if (this->_chessPieceNode == nullptr) {
        std::cerr << "updatePlayerPos: Error: ChessPieceNode is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (this->_PlayerPosition.getVecPosConverted() == irr::core::vector3df(0, 0, 0))
        std::cout << "updatePlayerPos: Warning: PlayerPosition is not setted" << std::endl;
    this->_chessPieceNode->setPosition(this->_PlayerPosition.getVecPosConverted());
    if (this->_PlayerPosition.getVecRotConverted() == irr::core::vector3df(0, 0, 0))
        std::cout << "updatePlayerPos: Warning: PlayerRotation is not setted" << std::endl;
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
    if (this->_chessPieceNode == nullptr) {
        std::cerr << "updateLevel: Error: ChessPieceNode is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_chessPieceNode->remove();
    chessPiece *_chessPieces = this->_ParentGame->getChessPieces();
    if (_chessPieces == nullptr) {
        std::cerr << "updateLevel: Error: ChessPieces wasn't correctly getted" << std::endl;
        exit(EXIT_FAILURE);
    }
    this-> _chessPieceNode = _chessPieces->placePiece(
        _chessPieces->getPiece(_PieceType),
        this->_PlayerPosition.getVecPosConverted(),
        this->_PlayerPosition.getVecRotConverted(),
        WHITE);
}
