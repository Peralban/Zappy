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
#include "../interface/AError.hpp"

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
         * @brief Sets the team of the player using the name of the team.
         * 
         * @param team string of the team name.
         */
        void setTeamFromName(std::string team = "undefined");

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
         * @brief generate a uuid for the player.
         * 
         * @return A uuid string.
         */
        std::string generateUUID();

        /**
         * @brief Gets the team of the player.
         * 
         * @return A pointer to the Team object representing the player's team.
         */
        Team *getTeam();

        /**
         * @brief Gets the level of the player.
         * 
         * @return The level of the player.
         */
        int getLevel();

        /**
         * @brief Gets the uuod of the player.
         * 
         * @return The uuid of the player.
         */
        std::string getUUID();

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

        /**
         * @brief Sets the chess piece of the player.
         * 
         * @param piece A pointer to the chessPiece object representing the player's chess piece.
         */
        irr::scene::IAnimatedMeshSceneNode *getChessPieceNode();

        /**
         * @brief Sets the ID of the player.
         *
         * @param id The ID to be set for the player.
         */
        void setID(int id);

        /**
         * @brief Gets the ID of the player.
         *
         * @return The ID of the player.
         */
        int getID();

        /**
         * @brief Sets the orientation of the player.
         *
         * @param orientation The orientation to be set for the player.
         */
        void setOrientation(int orientation);

        /**
         * @brief Gets the orientation of the player.
         *
         * @return The orientation of the player.
         */
        int getOrientation();

        /**
         * @brief Sets the inventory of the player.
         *
         * @param food The food level to be set for the player.
         * @param linemate The linemate level to be set for the player.
         * @param deraumere The deraumere level to be set for the player.
         * @param sibur The sibur level to be set for the player.
         * @param mendiane The mendiane level to be set for the player.
         * @param phiras The phiras level to be set for the player.
         * @param thystame The thystame level to be set for the player.
         */
        void setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

        /**
         * @brief Prints the inventory of the player.
         */
        void printInventory();

        /**
         * @brief Sets the broadcast message of the player.
         *
         * @param message The message to be set for the player.
         */
        void setBroadcastMessage(std::string message);

        /**
         * @brief Gets the broadcast message of the player.
         *
         * @return The broadcast message of the player.
         */
        std::string getBroadcastMessage();

        class NullableParentGame : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Trying to set ParentGame but given parentGame is null".
             */
            NullableParentGame() : AError("Trying to set ParentGame but given parentGame is null") {}
        };

        class ChessPieceUnset : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "ChessPiece is not setted".
             */
            ChessPieceUnset() : AError("ChessPiece is not setted") {}
        };

        class ChessPieceNotGetted : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "ChessPieces wasn't correctly getted".
             */
            ChessPieceNotGetted() : AError("ChessPieces wasn't correctly getted") {}
        };

        class ChessPieceNodeUnset : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "ChessPieceNode is not setted".
             */
            ChessPieceNodeUnset() : AError("ChessPieceNode is not setted") {}
        };

        class UnsetParentGame : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Trying to get ParentGame but ParentGame is not setted.".
             */
            UnsetParentGame() : AError("Trying to get ParentGame but ParentGame is not setted.") {}
        };

    private:
        std::string _Name; /**< The name of the player. */
        std::string _UUID; /**<The uuid of the player generated by default when created. */
        int _Level; /**< The level of the player. */
        int _Id; /**< The id of the player. */
        int _Orientation; /**< The orientation of the player. */

        int _food; /**< The food level of the player. */
        int _linemate; /**< The linemate level of the player. */
        int _deraumere; /**< The deraumere level of the player. */
        int _sibur; /**< The sibur level of the player. */
        int _mendiane; /**< The mendiane level of the player. */
        int _phiras; /**< The phiras level of the player. */
        int _thystame; /**< The thystame level of the player. */
        std::string _broadcastMessage = ""; /**< The broadcast message of the player. */

        pieceType _PieceType; /**< The type of chess piece. */
        PlayerPos _PlayerPosition; /**< The position of the player. */
        Team *_PlayerTeam; /**< A pointer to the Team object representing the player's team. */

        irr::scene::IAnimatedMeshSceneNode *_chessPieceNode; /**< The animated mesh scene node representing the chess piece. */
        ZappyGame *_ParentGame; /**< A pointer to the parent ZappyGame object. */
};
