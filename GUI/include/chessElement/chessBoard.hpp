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
    private:
        const int width;
        const int height;
        const float tileSize;
        const ISceneManager *sceneManager;
        const video::IVideoDriver *driver;
        ITexture* whiteTexture;
        ITexture* blackTexture;
};