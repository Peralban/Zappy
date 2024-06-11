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

class chessBoard {
    public:
        chessBoard(irrlichtWindow *parentWindow,
            int width = 20, int height = 20, float tileSize = 10.0f);
        ~chessBoard();

        void createBoard();
    private:
        int _Width;
        int _Height;
        float _TileSize;

        irrlichtWindow *_ParentWindow;
        irr::scene::ISceneManager *_SceneManager;
        irr::video::IVideoDriver *_Driver;
        irr::video::ITexture* _WhiteTexture;
        irr::video::ITexture* _BlackTexture;
};
