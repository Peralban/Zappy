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

/**
 * @class Player
 * @brief The Player class represents a player in the Zappy game.
 * 
 * This class provides functionalities to manage a player's attributes and actions.
 */
class Player {
    public:
        /**
         * @brief Constructs a Player object with the given name.
         * 
         * @param name The name of the player.
         */
        Player(std::string name = "undefined");

        /**
         * @brief Constructs a Player object with the given parent game and name.
         * 
         * @param parentGame A pointer to the parent ZappyGame object.
         * @param name The name of the player.
         */
        Player(ZappyGame *parentGame, std::string name = "undefined");

        /**
         * @brief Destroys the Player object.
         */
        ~Player();

        /**
         * @brief Sets the parent game of the player.
         * 
         * @param parentGame A pointer to the parent ZappyGame object.
         */
        void setParentGame(ZappyGame *parentGame);

        /**
         * @brief Initializes the player.
         * 
         * this will create the player's chess piece and set its position.
         */
        void playerInit();

        /**
         * @brief Sets the team of the player.
         * 
         * @param team A pointer to the Team object representing the player's team.
         */
        void setTeam(Team *team = nullptr);

        /**
         * @brief Sets the name of the player.
         * 
         * @param name The name of the player.
         */
        void setName(std::string name = "undefined");

        /**
         * @brief Updates the player's position.
         * 
         * used when his position changes so the chess piece will move on the window.
         */
        void updatePlayerPos();

        /**
         * @brief Sets the level of the player.
         * 
         * @param level The level of the player.
         */
        void setLevel(int level = 0);

        /**
         * @brief Sets the position of the player.
         * 
         * @param pos A pointer to the PlayerPos object representing the player's position.
         */
        void setPlayerPosition(PlayerPos *pos = nullptr);

        /**
         * @brief Updates the player's level.
         */
        void updateLevel();

        /**
         * @brief Gets the name of the player.
         * 
         * @return The name of the player.
         */
        std::string getName();

        /**
         * @brief Gets the parent game of the player.
         * 
         * @return A pointer to the parent ZappyGame object.
         */
        ZappyGame *getParentGame();

        /**
         * @brief Gets the position of the player.
         * 
         * @return A pointer to the PlayerPos object representing the player's position.
         */
        PlayerPos *getPlayerPosition();

    private:
        std::string _Name; /**< The name of the player. */
        int _Level; /**< The level of the player. */

        pieceType _PieceType; /**< The type of chess piece. */
        PlayerPos _PlayerPosition; /**< The position of the player. */
        Team *_PlayerTeam; /**< A pointer to the Team object representing the player's team. */

        irr::scene::IAnimatedMeshSceneNode *_chessPieceNode; /**< The animated mesh scene node representing the chess piece. */
        ZappyGame *_ParentGame; /**< A pointer to the parent ZappyGame object. */
};
