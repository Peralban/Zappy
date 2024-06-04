/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** player
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "team.hpp"
#include "playerInventory.hpp"
#include "playerPosition.hpp"
#include "chessElement/chessPiece.hpp"
#include <string>

class ZappyGame;
class chessPiece;

class Player {
    public:
        Player(std::string name = "undefined");
        Player(ZappyGame *parentGame, std::string name = "undefined");
        ~Player();

        void setParentGame(ZappyGame *parentGame);
        void playerInit();
        void setTeam(Team *team);
        void setName(std::string name);
        void updatePlayerPos();
        void setLevel(int level);
        void setPlayerPosition(PlayerPos *pos);
        void updateLevel();

        std::string getName();
        ZappyGame *getParentGame();
        PlayerPos *getPlayerPosition();
        

 
    private:
        std::string _Name;
        int _Level;
        pieceType _PieceType;
        PlayerPos _PlayerPosition;
        Team *_PlayerTeam;
        playerInventoy _Inventory;
        irr::scene::IAnimatedMeshSceneNode *_chessPieceNode;
        ZappyGame *_ParentGame;
};
