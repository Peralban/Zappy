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

class Player {
    public:
        Player();
        ~Player();
    private:
        int _Level;
        PlayerPos _PlalyerPosition;
        Team *_PlayerTeam;
        playerInventoy _Inventory;
};
