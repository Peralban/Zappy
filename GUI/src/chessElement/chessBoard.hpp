/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#pragma once

#include "irrlicht/irrlicht.h"

class chessBoard {
    public:
        chessBoard(irr::scene::ISceneManager *device, irr::video::IVideoDriver *driver,
            int width, int height, float tileSize);
        ~chessBoard();

        void createBoard();
    private:
        int _Width;
        int _Height;
        float _TileSize;
        irr::scene::ISceneManager *_SceneManager;
        irr::video::IVideoDriver *_Driver;
        irr::video::ITexture* _WhiteTexture;
        irr::video::ITexture* _BlackTexture;
};
