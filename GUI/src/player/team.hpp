/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** team
*/

#pragma once

#include <string>
#include "chessElement/chessPiece.hpp"

class Team {
    public:
        Team();
        ~Team();

        void setColor(teamColor color);
        void setTeamName(std::string name);

        teamColor getColor();
        std::string getTeamName();
    private:
        teamColor _Color;
        std::string _TeamName;
};
