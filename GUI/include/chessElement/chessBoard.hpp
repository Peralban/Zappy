/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessBoard
*/

#pragma once

#include "main.hpp"

class chessBoard {
    public:
        chessBoard(ISceneManager *device, video::IVideoDriver *driver,
            int width, int height, float tileSize);
        ~chessBoard();

        void createBoard();
    private:
        int _Width;
        int _Height;
        float _TileSize;
        ISceneManager *_SceneManager;
        video::IVideoDriver *_Driver;
        ITexture* _WhiteTexture;
        ITexture* _BlackTexture;
};