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
    private:
        irrlichtWindow *_ParentDevice;
        std::map<std::string, Player> playerList;
        chessPiece *_chessPieces;
};
