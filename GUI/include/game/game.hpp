/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** game
*/

#pragma once

#include "main.hpp"
#include "player/player.hpp"

class Game {
    public:
        Game();
        ~Game();
    private:
        std::map<std::string, Player> playerList;
};
