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
    this->_UUID = generateUUID();
}

Player::Player(ZappyGame *parentGame, std::string name) :
_PlayerPosition(PlayerPos(this))
{
    this->_Level = 0;
    this->_chessPieceNode = nullptr;
    this->_ParentGame = parentGame;
    this->_Name = name;
    this->_PieceType = PAWN;
    this->_PlayerTeam = nullptr;
    this->_UUID = generateUUID();
}

Player::~Player()
{
    this->_chessPieceNode->remove();
    std::cout << "\nPlayer destroyed\n" << std::endl;
}

void Player::setParentGame(ZappyGame *parentGame)
{
    if (parentGame == nullptr) {
        throw NullableParentGame();
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
        this
    );
}

void Player::setTeam(Team *team)
{
    if (team == nullptr) {
        std::cout << "setTeam: Warning: Team is not setted" << std::endl;
    }
    if (this->_PlayerTeam != nullptr) {
        std::cout << "setTeam: Warning: Player already has a team" << std::endl;
    }
    this->_PlayerTeam = team;
    if (team->getColor() != nullptr) {
        this->_chessPieceNode->setMaterialTexture(0, team->getColor());
    } else {
        std::cout << "setTeam: Warning: Team has no color" << std::endl;
    }
}

void Player::setTeamFromName(std::string teamName)
{
    if (this->_ParentGame == nullptr) {
        std::cout << "setTeamFromName: Warning: ParentGame is not setted setting team to null" << std::endl;
        this->_PlayerTeam = nullptr;
        return;
    }
    if (this->_ParentGame->getTeamFromName(teamName) == nullptr) {
        std::cout << "setTeamFromName: Warning: Team not found setting team to null" << std::endl;
        this->_PlayerTeam = nullptr;
        return;
    }
    this->_PlayerTeam = this->_ParentGame->getTeamFromName(teamName);
    if (this->_PlayerTeam->getColor() != nullptr) {
        this->_chessPieceNode->setMaterialTexture(0, this->_PlayerTeam->getColor());
    } else {
        std::cout << "setTeamFromName: Warning: Team has no color" << std::endl;
    }
}


void Player::setPlayerPosition(PlayerPos *pos)
{
    if (pos == nullptr) {
        std::cout << "setPlayerPosition: waning: pos is null" << std::endl;
    }
    this->_PlayerPosition = *pos;
}

void Player::updatePlayerPos()
{
    if (this->_chessPieceNode == nullptr) {
        throw ChessPieceUnset();
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
        this);
}

std::string Player::getUUID()
{
    return this->_UUID;
}

std::string Player::generateUUID()
{
    std::string uuid = "";
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int length = 16;

    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % characters.length();
        uuid += characters[randomIndex];
    }

    return uuid;
}

Team *Player::getTeam()
{
    if (this->_PlayerTeam == nullptr) {
        std::cout << "getTeam: Warning: PlayerTeam is not setted" << std::endl;
    }
    return this->_PlayerTeam;
}

int Player::getLevel()
{
    return this->_Level;
}

std::string Player::getName()
{
    return this->_Name;
}

PlayerPos *Player::getPlayerPosition()
{
    return &this->_PlayerPosition;
}

ZappyGame *Player::getParentGame()
{
    if (this->_ParentGame == nullptr) {
        throw UnsetParentGame();
    }
    return this->_ParentGame;
}

