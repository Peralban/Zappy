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
    this->_TeamTexture = nullptr;
    this->_ColorName = "undefined";
};

Team::~Team()
{
};

void Team::setColor(irr::video::ITexture *texture, std::string colorName)
{
    if (!texture) {
        std::cout << "setColor: Error: No texture set for team." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (colorName == "undefined") {
        std::cout << "setColor: Warning: No color name set for team." << std::endl;
    }
    if (this->_TeamTexture) {
        std::cout << "setColor: Warning: Team already has a color set." << std::endl;
    }
    this->_TeamTexture = texture;
    this->_ColorName = colorName;
}

void Team::setTeamName(std::string name)
{
    if (name == "undefined") {
        std::cout << "setTeamName: Warning: Team name is undefined, name is not setted" << std::endl;
        return;
    }
    this->_TeamName = name;
}

irr::video::ITexture *Team::getColor()
{
    if (!this->_TeamTexture) {
        std::cout << "getColor: Warning: No color set for team." << std::endl;
    }
    return this->_TeamTexture;
}

std::string Team::getTeamName()
{
    if (this->_TeamName == "undefined") {
        std::cout << "getTeamName: Warning: Team name is undefined." << std::endl;
    }
    return this->_TeamName;
}
