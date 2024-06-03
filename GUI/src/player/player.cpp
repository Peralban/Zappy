/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** player
*/

#include "player/player.hpp"

#include "game/ZappyGame.hpp"
#include "chessElement/chessPiece.hpp"

Player::Player()
{
    this->_Level = 0;
    this->_PlayerTeam = nullptr;
}

Player::~Player()
{
}

ZappyGame *Player::getParentGame()
{
    return this->_ParentGame;
}

void Player::setParentGame(ZappyGame *parentGame)
{
    this->_ParentGame = parentGame;
}

void Player::playerInit()
{
    std::cout << "Player init" << std::endl;
    chessPiece *_chessPieces = this->_ParentGame->getChessPieces();
    std::cout << "Chess pieces loaded" << std::endl;
    this-> _chessPieceNode = _chessPieces->placePiece(_chessPieces->getPiece(PAWN), vector3df(40, 5, 40), WHITE);
    std::cout << "Piece placed" << std::endl;
}