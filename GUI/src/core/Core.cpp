/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** Core
*/
#include "Core.hpp"
#include <iostream>

Core::Core(int width, int height, int platformX, int platformY, float tileSize, quality gameQuality, bool debug)
    : m_window(width, height, irr::video::EDT_OPENGL, gameQuality, debug),
      m_client(new guiNetworkClient()),
      m_zappy(new ZappyGame())
{
    m_zappy->setPlatformSize(platformX, platformY);
    m_zappy->setTileSize(tileSize);
}

Core::~Core()
{
    delete m_client;
    delete m_zappy;
}

void Core::initialize(int ac, char **av)
{
    std::cout << "Starting Zappy" << std::endl;

    try {
        m_window.parseArgs(ac, av);
        m_window.windowCreateDevice();

        if (m_window.getDevice() == nullptr)
        {
            std::cerr << "Failed to create Irrlicht device!" << std::endl;
            std::exit(1);
        }

        m_window.initDrivers();
        m_window.initLoader();
        m_window.initCamera();
        m_window.initEventReceiver();

        std::cout << " -------------- LINKING CLIENT AND ZAPPY -------------- " << std::endl;
        m_window.linkZappyGame(m_zappy);
        m_window.linkGuiClient(m_client);

        std::cout << " -------------- CREATING SOCKET -------------- " << std::endl;
        m_client->createSocket();

        std::cout << " -------------- INITIALIZING IDENTIFICATION -------------- " << std::endl;
        m_client->askInitData();

        std::cout << " -------------- INITIALIZING CHESS BOARD -------------- " << std::endl;
        m_client->makeNonBlocking();

        m_zappy->loadChessPieces();
        m_zappy->addPlayer("player1");
        m_zappy->getPlayer("player1")->getPlayerPosition()->setPos(5, 3);
        m_zappy->getPlayer("player1")->getPlayerPosition()->setZ(2);
        m_zappy->getPlayer("player1")->getPlayerPosition()->setOrientation(0, 0, 2);
        m_zappy->getPlayer("player1")->updatePlayerPos();
        m_zappy->getPlayer("player1")->setLevel(2);
    } catch (std::exception &e) {
        exit(84);
    }
}

void Core::run()
{
    std::cout << " -------------- RUNNING WINDOW -------------- " << std::endl;
    m_window.runWindow(m_zappy, m_client);
}
