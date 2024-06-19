#include "Core.hpp"
#include <iostream>

Core::Core(int argc, char **argv)
    : m_window(1920, 1080, 30, 10, 15.0f, irr::video::EDT_OPENGL, MID, false)
{
    
    this->m_argc = argc;
    this->m_argv = argv;
    this->m_client = nullptr;
    this->m_zappy = nullptr;
}

void Core::initialize()
{
    std::cout << "Starting Zappy" << std::endl;
    m_client = new guiNetworkClient();
    m_zappy = new ZappyGame();

    m_window.parseArgs(m_argc, m_argv);
    m_window.windowCreateDevice();

    if (m_window.getDevice() == nullptr)
        std::exit(1);

    m_window.initDrivers();
    m_window.initLoader();
    m_window.initCamera();
    m_window.initChessBoard();
    m_window.initEventReceiver();

    m_window.linkZappyGame(m_zappy);
    m_window.linkGuiClient(m_client);

    m_client->createSocket();
    m_client->initIdentification();
    std::cout << "map size is " << m_client->getMapSize() << std::endl;
    std::cout << "time unit is " << m_client->getTimeUnit() << std::endl;
    m_client->makeNonBlocking();

    m_zappy->loadChessPieces();
    m_zappy->addPlayer("player1");
    m_zappy->getPlayer("player1")->getPlayerPosition()->setPos(5, 3);
    m_zappy->getPlayer("player1")->getPlayerPosition()->setConvertedZ(5.0f);
    m_zappy->getPlayer("player1")->getPlayerPosition()->setOrientation(0, 0, 2);
    m_zappy->getPlayer("player1")->updatePlayerPos();
    m_zappy->getPlayer("player1")->setLevel(2);
}

void Core::run()
{
    std::cout << " -------------- RUNNING WINDOW -------------- " << std::endl;
    m_window.runWindow();
}
