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
        chessBoard();
        chessBoard(ISceneManager *device, video::IVideoDriver *driver,
            int width, int height, float tileSize);
        ~chessBoard();

        void createBoard();
    private:
        int width;
        int height;
        float tileSize;
        ISceneManager *sceneManager;
        video::IVideoDriver *driver;
        ITexture* whiteTexture;
        ITexture* blackTexture;
};