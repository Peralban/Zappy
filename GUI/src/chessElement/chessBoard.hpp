/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "loader/textureLoader.hpp"
#include <vector>

class ZappyGame;
class irrlichtWindow;

class Tile {
    public:
        Tile() : _food(0), _linemate(0), _deraumere(0), _sibur(0), _mendiane(0), _phiras(0), _thystame(0), _player(0), _egg(0) {}
        ~Tile() = default;

        void setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
        {
            this->_food = food;
            this->_linemate = linemate;
            this->_deraumere = deraumere;
            this->_sibur = sibur;
            this->_mendiane = mendiane;
            this->_phiras = phiras;
            this->_thystame = thystame;
        }

        void printInventory()
        {
            std::cout << "food: " << _food << std::endl;
            std::cout << "linemate: " << _linemate << std::endl;
            std::cout << "deraumere: " << _deraumere << std::endl;
            std::cout << "sibur: " << _sibur << std::endl;
            std::cout << "mendiane: " << _mendiane << std::endl;
            std::cout << "phiras: " << _phiras << std::endl;
            std::cout << "thystame: " << _thystame << std::endl;
            std::cout << "player: " << _player << std::endl;
            std::cout << "egg: " << _egg << std::endl;
        }

        void setPlayer(int player) { this->_player = player; }
        void setEgg(int egg) { this->_egg = egg; }

        int getPlayer() { return _player; }
        int getEgg() { return _egg; }

    private:
        int _food;
        int _linemate;
        int _deraumere;
        int _sibur;
        int _mendiane;
        int _phiras;
        int _thystame;
        int _player;
        int _egg;
};

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

        void InitMap(int width, int height);

        void updateMapBtc(std::string response);

        void printMap();

        void printMapAtPos(int x, int y);

        /**
         * @brief Returns the status of the creation of the board
         * 
         * @return a boolean value that indicates whether the board has been created or not.
         */
        bool isCreated();


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

        irr::video::ITexture* _WhiteTexture; ///< A pointer to the white texture used for rendering the tiles.
        irr::video::ITexture* _BlackTexture; ///< A pointer to the black texture used for rendering the tiles.
};
