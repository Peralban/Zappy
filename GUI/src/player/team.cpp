/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** team
*/

#include "chessElement/chessPiece.hpp"
#include "team.hpp"

Team::Team()
{
    this->_TeamName = "undefined";
    this->_Color = DEFAULT;
};

Team::~Team()
{
};

void Team::setColor(teamColor color)
{
    this->_Color = color;
}

void Team::setTeamName(std::string name)
{
    this->_TeamName = name;
}

teamColor Team::getColor()
{
    return this->_Color;
}

std::string Team::getTeamName()
{
    return this->_TeamName;
}
