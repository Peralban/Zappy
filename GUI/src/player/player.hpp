/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** player
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "team.hpp"
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
        void setTeam(Team *team = nullptr);
        void setName(std::string name = "undefined");
        void updatePlayerPos();
        void setLevel(int level = 0);
        void setPlayerPosition(PlayerPos *pos = nullptr);
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
        irr::scene::IAnimatedMeshSceneNode *_chessPieceNode;
        ZappyGame *_ParentGame;
};
