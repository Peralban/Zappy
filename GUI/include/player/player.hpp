/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** player
*/

#pragma once

#include "main.hpp"
#include "player/team.hpp"
#include "player/playerInventory.hpp"
#include "player/playerPosition.hpp"

class ZappyGame;
class chessPiece;

class Player {
    public:
        Player();
        ~Player();

        ZappyGame *getParentGame();
        void setParentGame(ZappyGame *parentGame);
        void playerInit();
    private:
        int _Level;
        PlayerPos _PlalyerPosition;
        Team *_PlayerTeam;
        playerInventoy _Inventory;
        IAnimatedMeshSceneNode *_chessPieceNode;
        ZappyGame *_ParentGame;
};
