/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** team
*/

#pragma once

#include <string>
#include <iostream>
#include "chessElement/chessPiece.hpp"

/**
 * @class Team
 * @brief Represents a team in the game.
 */
class Team {
    public:
        /**
         * @brief Default constructor for Team class.
         */
        Team();

        /**
         * @brief Destructor for Team class.
         */
        ~Team();

        /**
         * @brief Sets the color of the team.
         * @param color The color of the team.
         */
        void setColor(irr::video::ITexture *texture, std::string colorName);

        /**
         * @brief Sets the name of the team.
         * @param name The name of the team.
         */
        void setTeamName(std::string name);

        /**
         * @brief Gets the color of the team.
         * @return The color of the team.
         */
        irr::video::ITexture *getColor();

        /**
         * @brief Gets the name of the team.
         * @return The name of the team.
         */
        std::string getTeamName();

    private:
        std::string _ColorName; /**< The name of the color of the team. */
        irr::video::ITexture *_TeamTexture; /**< The color of the team. */
        std::string _TeamName; /**< The name of the team. */
};
