/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "chessElement/chessPiece.hpp"
#include "player/player.hpp"
#include "event/serverDataReceiver.hpp"
#include "chessElement/chessBoard.hpp"
#include <iostream>

class irrlichtWindow;

/**
 * @brief The ZappyGame class represents the game logic for the Zappy game.
 * 
 * This class manages the game state, including the chess pieces, players, and time unit.
 * It provides functions to interact with the game, such as adding players, setting the time unit, and printing server messages.
 */
class ZappyGame {
    public:
        /**
         * @brief Constructs a ZappyGame object.
         */
        ZappyGame();

        /**
         * @brief Destroys the ZappyGame object.
         */
        ~ZappyGame();

        /**
         * @brief Links the ZappyGame with an irrlichtWindow object.
         * 
         * @param parentDevice The irrlichtWindow object to link with.
         */
        void linkWithDevice(irrlichtWindow *parentDevice);

        /**
         * @brief Sets the server data parser object.
         * 
         * @param serverDataParser The server data parser object to set.
         */
        void setServerDataParser(ServerDataParser *serverDataParser);

        /**
         * @brief Loads every chess pieces for the game so they will be loaded only one time.
         * 
         * used for performance reasons.
         */
        void loadChessPieces();
        
        /**
         * @brief Adds a player to the game.
         * 
         * @param name The name of the player to add.
         * 
         * used when a player connects to the server or when a new player is created.
         */
        void addPlayer(std::string name);

        /**
         * @brief Sets the time unit for the game.
         * 
         * @param timeUnit The time unit to set.
         * 
         * The time unit is the number of action per second.
         */
        void setTimeUnit(int timeUnit);

        /**
         * @brief Sets the size of the platform.
         * 
         * @param x The width of the platform.
         * @param y The height of the platform.
        */
        void setPlatformSize(int x, int y);

        /**
         * @brief Sets the size of each tile of the platform.
         * 
         * @param tileSize The size of each tile.
        */
        void setTileSize(float tileSize);

        /**
         * @brief Sets the width of the platform.
         * 
         * @param width The width of the platform.
        */
        void setPlatformWidth(int width);

        /**
         * @brief Sets the height of the platform.
         * 
         * @param height The height of the platform.
        */
        void setPlatformHeight(int height);

        /**
         * @brief Initializes the server events for the game.
         * 
         * This function initializes the server data parser object.
         */
        void initServerEvents();

        /**
         * @brief Creates a team with the specified name.
         * 
         * @param teams The name of the team to create.
         */
        void createTeam(std::string teams, int Red, int Green, int Blue, int Alpha);
        
        /**
         * @brief Gets the chess pieces of the game.
         * 
         * @return A pointer to the chess pieces object.
         */
        chessPiece *getChessPieces();

        /**
         * @brief Gets the parent irrlichtWindow object of the game.
         * 
         * @return A pointer to the parent irrlichtWindow object.
         */
        irrlichtWindow *getParentDevice();

        /**
         * @brief Gets the time unit of the game.
         * 
         * @return The time unit.
         */
        int getTimeUnit();

        /**
         * @brief Gets the width of the platform.
         * 
         * @return The width of the platform.
        */
        int getPlatformWidth();

        /**
         * @brief Gets the height of the platform.
         * 
         * @return The height of the platform.
        */
        int getPlatformHeight();

        /**
         * @brief Gets the size of each tile of the platform.
         *  
         * @return The size of each tile.
        */
        float getTileSize();

        /**
         * @brief Gets the list of players in the game.
         * 
         * @return A pointer to the list of players.
         */
        std::map<std::string, Player*> *getPlayerList();

        /**
         * @brief Gets a player by name.
         * 
         * @param name The name of the player to get.
         * @return A pointer to the player.
         */
        Player *getPlayer(std::string name);;

        /**
         * @brief Gets the server data parser object.
         * 
         * @return A pointer to the server data parser object.
        */
        ServerDataParser *getServerDataParser();

        /**
         * @brief Gets the chess board object.
         * 
         * @return A pointer to the chess board object.
         */
        chessBoard *getChessBoard();

        /**
         * @brief Adds a new player to the game.
         *
         * This function is called when a new player connects to the server.
         * The command string should contain the necessary information to create a new player.
         *
         * @param cmd The command string received from the server.
         */
        void newPlayer(std::string cmd);

        /**
         * @brief Updates the position of a player in the game.
         *
         * This function is called when a player moves in the game.
         * The command string should contain the necessary information to update the player's position.
         *
         * @param cmd The command string received from the server.
         */
        void updatePlayerPos(std::string cmd);

        /**
         * @brief Updates the level of a player in the game.
         *
         * This function is called when a player levels up in the game.
         * The command string should contain the necessary information to update the player's level.
         *
         * @param cmd The command string received from the server.
         */
        void updatePlayerLevel(std::string cmd);

        /**
         * @brief Updates the inventory of a player in the game.
         *
         * This function is called when a player's inventory changes in the game.
         * The command string should contain the necessary information to update the player's inventory.
         *
         * @param cmd The command string received from the server.
         */
        void updatePlayerInventory(std::string cmd);

        /**
         * @brief Adds a new egg to the game.
         *
         * This function is called when a player lays an egg in the game.
         * The command string should contain the necessary information to create a new egg.
         *
         * @param cmd The command string received from the server.
         */
        void newEgg(std::string cmd);

        /**
         * @brief Handles a broadcast message in the game.
         *
         * This function is called when a player sends a broadcast message in the game.
         * The command string should contain the necessary information to handle the broadcast message.
         *
         * @param cmd The command string received from the server.
         */
        void broadcastMessage(std::string cmd);

        /**
         * @brief Handles a player's death in the game.
         *
         * This function is called when a player dies in the game.
         * The command string should contain the necessary information to handle the player's death.
         *
         * @param cmd The command string received from the server.
         */
        void playerDie(std::string cmd);

        /**
         * @brief Gets the team object from the team name.
         * 
         * @param teamName The name of the team to get.
         * @return A pointer to the team object.
         */
        Team *getTeamFromName(std::string teamName);

        /**
         * @brief Gets the list of teams in the game.
         * 
         * @return A pointer to the list of teams.
         */
        std::map<std::string, Team*> *getTeamsList();

        /**
         * @brief Creates a team with the specified name.
         * 
         * @param teamName The name of the team to create.
         * @param Red The red color of the team.
         * @param Green The green color of the team.
         * @param Blue The blue color of the team.
         * @param Alpha The alpha color of the team.
         * @return A pointer to the team object.
         */
        Team *createGetTeam(std::string teamName, int Red, int Green, int Blue, int Alpha);

        /**
         * @brief Deletes a player from the game by their name.
         *
         * This function removes a player from the game's player list using their name as the key.
         * If the player does not exist in the list, no action is performed.
         *
         * @param name The name of the player to delete.
         */
        void deletePlayer(std::string name);

        /**
         * @brief Deletes a player from the game by their Player object.
         *
         * This function removes a player from the game's player list using their Player object.
         * If the player does not exist in the list, no action is performed.
         *
         * @param player A pointer to the Player object of the player to delete.
         */
        void deletePlayer(Player *player);

        class NullableParentDevice : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Trying to link with device but given parentDevice is null.".
             */
            NullableParentDevice() : AError("Trying to link with device but given parentDevice is null.") {}
        };

        class UnsetParentDevice : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "ParentDevice is not setted.".
             */
            UnsetParentDevice() : AError("ParentDevice is not setted") {}
        };

        class NullableServerDataParser : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Trying to set ServerDataParser but given serverDataParser is null".
             */
            NullableServerDataParser() : AError("Trying to set ServerDataParser but given serverDataParser is null.") {}
        };

        class UnsetServerDataParser : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "ServerDataParser is not setted".
             */
            UnsetServerDataParser() : AError("ServerDataParser is not setted.") {}
        };

        class UnableCreateChessPiece : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Couldn't create chessPieces".
             */
            UnableCreateChessPiece() : AError("Couldn't create chessPieces.") {}
        };

        class UnableCreatePlayer : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Couldn't create player.".
             */
            UnableCreatePlayer() : AError("Couldn't create player.") {}
        };

    private:
        irrlichtWindow *_ParentDevice; /**< The parent irrlichtWindow object. */

        chessPiece *_chessPieces; /**< The chess pieces Object. */

        int _PlatformX; /** < The Width X of the platform */
        int _PlatformY; /** < The Height Y of the platform */
        float _TileSize; /** < The size of each tile of the platform */

        ServerDataParser *_serverDataParser; /**< The server data parser object. */

        chessBoard *_chessBoard; /**< The chess board object. */
    
        std::map<std::string, Player*> _playerList; /**< The list of players in the game. */

        int _TimeUnit; /**< The time unit of the game. */

        std::map<std::string, Team*> _teamsList; /**< A map of Teams names to Teams objects. */
};
