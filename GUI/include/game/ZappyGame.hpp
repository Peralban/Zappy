/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#pragma once

#include "main.hpp"
#include "chessElement/chessPiece.hpp"
#include "player/player.hpp"

class irrlichtWindow;

class ZappyGame {
    public:
        ZappyGame();
        ~ZappyGame();

        void linkWithDevice(irrlichtWindow *parentDevice);
        void loadChessPieces();
        
        void addPlayer(std::string name);
        
        chessPiece *getChessPieces();
        irrlichtWindow *getParentDevice();

        std::vector<std::pair<std::string, Player*>> *getPlayerList();
        Player *getPlayer(std::string name);
    private:
        irrlichtWindow *_ParentDevice;
        chessPiece *_chessPieces;
        std::vector<std::pair<std::string, Player*>> _playerList;

};
