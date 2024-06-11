/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** irrlichtWindow
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "game/ZappyGame.hpp"
#include "chessElement/chessBoard.hpp"
#include "event/irrlichtEventHandler.hpp"
#include "networkGui/guiClient.hpp"

class guiNetworkClient;

class irrlichtWindow {
    public:
        irrlichtWindow(
            int width, int height,
            int platformX, int platformY,
            float tileSize, irr::video::E_DRIVER_TYPE driverType,
            quality selectedQuality, bool debug);
        ~irrlichtWindow();

        void windowCreateDevice();
        void initDrivers();
        void initChessBoard();
        void initEventReceiver();
        void initCamera();
        void linkZappyGame(ZappyGame *ZappyGameToLink);
        void linkGuiClient(guiNetworkClient *GuiClientToLink);
        void updateNetwork();

        int runWindow();

        irr::IrrlichtDevice *getDevice();
        irr::video::IVideoDriver *getDriver();
        irr::scene::ISceneManager *getSceneManager();
        quality getQuality();
        ZappyGame *getLinkedZappyGame();
        guiNetworkClient *getGuiClient();

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

        int _socket;

        bool _Debug;

        quality _Quality;
        irr::IrrlichtDevice *_Device;
        irr::video::IVideoDriver *_Driver;
        irr::scene::ISceneManager *_SceneManager;
        irr::video::E_DRIVER_TYPE _DriverType;
        chessBoard *_chessBoard;
        myEventReceiver *_EventReceiver;
        ZappyGame *_LinkedZappyGame;
        guiNetworkClient *_LinkedGuiClient;
};
