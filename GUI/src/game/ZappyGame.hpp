/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "chessElement/chessPiece.hpp"
#include "player/player.hpp"
#include <iostream>
#include <vector>

class irrlichtWindow;

class ZappyGame {
    public:
        ZappyGame();
        ~ZappyGame();

        void linkWithDevice(irrlichtWindow *parentDevice);
        void loadChessPieces();
        
        void addPlayer(std::string name);
        void setTimeUnit(int timeUnit);
        
        chessPiece *getChessPieces();
        irrlichtWindow *getParentDevice();

        int getTimeUnit();

        std::vector<std::pair<std::string, Player*>> *getPlayerList();
        Player *getPlayer(std::string name);

        void printServerMessage(std::string message);
    private:
        irrlichtWindow *_ParentDevice;
        chessPiece *_chessPieces;
        std::vector<std::pair<std::string, Player*>> _playerList;

        int _TimeUnit;
};
