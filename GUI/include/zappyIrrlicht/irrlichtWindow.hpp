/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#pragma once

#include "main.hpp"
#include "game/ZappyGame.hpp"
#include "chessElement/chessBoard.hpp"
#include "event/irrlichtEventHandler.hpp"


class irrlichtWindow {
    public:
        irrlichtWindow(
            int width, int height,
            int platformX, int platformY,
            float tileSize, video::E_DRIVER_TYPE driverType,
            quality selectedQuality, bool debug);
        ~irrlichtWindow();

        void windowCreateDevice();
        void initDrivers();
        void initChessBoard();
        void initEventReceiver();
        void initCamera();
        void linkZappyGame(ZappyGame *ZappyGameToLink);
        int runWindow();

        IrrlichtDevice *getDevice();
        IVideoDriver *getDriver();
        ISceneManager *getSceneManager();
        quality getQuality();
        ZappyGame *getLinkedZappyGame();

        int getWidth();
        int getHeight();
        int getPlatformX();
        int getPlatformY();
        float getTileSize();

        bool getDebugState();


    private:
        int _Width;
        int _Height;
        int _PlatformX;
        int _PlatformY;
        float _TileSize;

        bool _Debug;

        quality _Quality;
        IrrlichtDevice *_Device;
        IVideoDriver *_Driver;
        ISceneManager *_SceneManager;
        video::E_DRIVER_TYPE _DriverType;
        chessBoard *_chessBoard;
        myEventReceiver *_EventReceiver;
        ZappyGame *_LinkedZappyGame;
};