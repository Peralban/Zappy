/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "loader/textureLoader.hpp"
#include "../interface/AError.hpp"
#include "chessElement/tiles.hpp"
#include <vector>

class items;
class ZappyGame;
class irrlichtWindow;

/**
 * @brief The chessBoard class represents a chess board in a GUI application.
 * 
 * This class provides functionality to create and manage a chess board in a GUI application.
 * It uses the irrlichtWindow class to render the board and the irr::scene::ISceneManager
 * and irr::video::IVideoDriver classes for scene management and video rendering respectively.
 */
class chessBoard {
    public:
        
        /**
         * @brief Constructs a chessBoard object with the specified parameters.
         * 
         * @param parentWindow A pointer to the irrlichtWindow object that will be used as the parent window.
         * @param width The width of the chess board in number of tiles.
         * @param height The height of the chess board in number of tiles.
         * @param tileSize The size of each tile in the chess board.
         */
        chessBoard(ZappyGame *ParentZappy,
            int width = -1, int height = -1, float tileSize = -1);

        chessBoard();

        /**
         * @brief Destroys the chessBoard object.
         */
        ~chessBoard();

        /**
         * @brief Sets the parent game of the chess board.
         * 
         * @param parentGame A pointer to the parent ZappyGame object.
         */
        void setParentWindow(irrlichtWindow *parentWindow);

        /**
         * @brief Sets the white texture for the chess board.
         * 
         * @param whiteTexture A pointer to the white texture.
         */
        void setTileSize(float tileSize);

        /**
         * @brief Sets the black texture for the chess board.
         * 
         * @param blackTexture A pointer to the black texture.
         */
        void setWidth(int width);

        /**
         * @brief Sets the width of the chess board.
         * 
         * @param width The width of the chess board.
         */
        void setHeight(int height);

        /**
         * @brief Creates the chess board.
         * 
         * This function creates the chess board by rendering the tiles using the specified textures.
         */
        void createBoard();

        /**
         * @brief Initializes the chess board.
         * 
         * This function initializes the chess board by creating the tiles and setting their positions.
         */
        void InitMap(int width, int height);

        /**
         * @brief Updates the chess board.
         * 
         * This function updates the chess's tiles inventory thanks to a server data
         */
        void updateMapBtc(std::string response);

        /**
         * @brief Prints the chess board.
         * 
         * This function prints the inventory of each tile on the chess board.
         */
        void printMap();

        /**
         * @brief Prints the chess board's tile inventory at the specified position.
         * 
         * @param x The x-coordinate of the position.
         * @param y The y-coordinate of the position.
         */
        void printMapAtPos(int x, int y);

        /**
         * @brief Updates the chess board.
         * 
         * This function updates the items on the chess board.
         */
        void updateMapItem();

        /**
         * @brief Returns the chess board's map.
         * 
         * @return A list of lists of Tile objects that represent the tiles of the chess board.
         */
        std::vector<std::vector<Tile *>> getMap();
        
        /**
         * @brief Returns the items handler of the chess board.
         * 
         * @return A pointer to the items object that is used to manage the items on the tiles.
         */
        items *getItemsHandler();

        /**
         * @brief Take a ressource from a tile. at
         * @param ressource The ressource to take.
         * @param x The x-coordinate of the tile.
         * @param y The y-coordinate of the tile.
         */
        void takeRessource(std::string ressource, int x, int y);

        /**
         * @brief Drop a ressource on a tile.
         * @param ressource The ressource to drop.
         * @param x The x-coordinate of the tile.
         * @param y The y-coordinate of the tile.
         */
        void dropRessource(std::string ressource, int x, int y);

        class NoParentWindow : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "No parent window set.".
             */
            NoParentWindow() : AError("No parent window set.") {}
        };

        class CouldNotLoadTexture : public AError {
            public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Could not load textures.".
             */
            CouldNotLoadTexture() : AError("Could not load textures.") {}
        };

        class InvalidTileSize : public AError {
            public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Invalid tile size".
             */
            InvalidTileSize() : AError("Invalid tile size.") {}
        };

        class InvalidWidth : public AError {
            public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Invalid width for chess board".
             */
            InvalidWidth() : AError("Invalid width for chess board.") {}
        };

        class InvalidHeight : public AError {
            public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Invalid height for chess board".
             */
            InvalidHeight() : AError("Invalid height for chess board.") {}
        };

        class NoSceneManager : public AError {
            public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "No scene manager set for chess board".
             */
            NoSceneManager() : AError("No scene manager set for chess board.") {}
        };

        class NoTexturesSet : public AError {
            public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "No textures set for chess board.".
             */
            NoTexturesSet() : AError("No textures set for chess board.") {}
        };

        /**
         * @brief Returns the status of the creation of the board
         * 
         * @return a boolean value that indicates whether the board has been created or not.
         */
        bool isCreated();

        /**
         * @brief Returns the parent window of the chess board.
         * 
         * @return A pointer to the irrlichtWindow object that is used as the parent window.
         */
        irrlichtWindow *getParentWindow();

    private:
        int _Width; ///< The width of the chess board in number of tiles.
        int _Height; ///< The height of the chess board in number of tiles.
        float _TileSize; ///< The size of each tile in the chess board.

        bool _IsCreated; ///< A boolean value that indicates whether the chess board has been created or not.

        irrlichtWindow *_ParentWindow; ///< A pointer to the irrlichtWindow object that is used as the parent window.
        irr::scene::ISceneManager *_SceneManager; ///< A pointer to the irr::scene::ISceneManager object for scene management.
        irr::video::IVideoDriver *_Driver; ///< A pointer to the irr::video::IVideoDriver object for video rendering.
        ZappyGame *_ParentGame; ///< A pointer to the ZappyGame object that is used as the parent game.
        std::vector<std::vector<Tile *>> _map; ///< A list of lists of Tile objects that represent the tiles of the chess board.

        items *_ItemsHandler; ///< A pointer to the items object that is used to manage the items on the tiles.

        irr::video::ITexture* _WhiteTexture; ///< A pointer to the white texture used for rendering the tiles.
        irr::video::ITexture* _BlackTexture; ///< A pointer to the black texture used for rendering the tiles.
};
