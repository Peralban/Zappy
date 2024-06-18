/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "loader/textureLoader.hpp"

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
        chessBoard(irrlichtWindow *parentWindow,
            int width = 20, int height = 20, float tileSize = 10.0f);

        /**
         * @brief Destroys the chessBoard object.
         */
        ~chessBoard();

        void setWidth(int width);

        void setHeight(int height);

        /**
         * @brief Creates the chess board.
         * 
         * This function creates the chess board by rendering the tiles using the specified textures.
         */
        void createBoard();

    private:
        int _Width; ///< The width of the chess board in number of tiles.
        int _Height; ///< The height of the chess board in number of tiles.
        float _TileSize; ///< The size of each tile in the chess board.

        irrlichtWindow *_ParentWindow; ///< A pointer to the irrlichtWindow object that is used as the parent window.
        irr::scene::ISceneManager *_SceneManager; ///< A pointer to the irr::scene::ISceneManager object for scene management.
        irr::video::IVideoDriver *_Driver; ///< A pointer to the irr::video::IVideoDriver object for video rendering.

        irr::video::ITexture* _WhiteTexture; ///< A pointer to the white texture used for rendering the tiles.
        irr::video::ITexture* _BlackTexture; ///< A pointer to the black texture used for rendering the tiles.
};
