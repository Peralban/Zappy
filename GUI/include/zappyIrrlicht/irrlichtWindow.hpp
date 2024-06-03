/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#pragma once

#include "main.hpp"
#include "event/irrlichtEventHandler.hpp"
#include "chessElement/chessBoard.hpp"
#include "chessElement/chessPiece.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"

class irrlichtWindow {
    public:
        irrlichtWindow(
            int width, int height,
            int platformX, int platformY,
            float tileSize, video::E_DRIVER_TYPE driverType);
        ~irrlichtWindow();

        void windowCreateDevice();
        void initDrivers();
        void initChessBoard();
        void initEventReceiver();
        void initCamera();
        void initChessPiece();

        int runWindow();

        IrrlichtDevice *getDevice();


    private:
        int _Width;
        int _Height;
        int _PlatformX;
        int _PlatformY;
        float _TileSize;
        IrrlichtDevice *_Device;
        IVideoDriver *_Driver;
        ISceneManager *_SceneManager;
        video::E_DRIVER_TYPE _DriverType;
        chessPiece *_chessPieces;
        chessBoard *_chessBoard;
        myEventReceiver *_EventReceiver;
        IAnimatedMeshSceneNode *_chessPieceNode;
};