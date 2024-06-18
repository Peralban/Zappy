/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#include "zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

int main(int ac, char **av)
{
	int width = 1920;
	int height = 1080;
	int platformX = 30;
	int platformY = 10;
	float tileSize = 15.0f;
	quality quality = MID;
	bool debug = false;

	std::cout << "Starting Zappy" << std::endl;
	guiNetworkClient *client = new guiNetworkClient();
	ZappyGame *zappy = new ZappyGame();

	irrlichtWindow window(width, height, platformX, platformY, tileSize, irr::video::EDT_OPENGL, quality, debug);
	window.parseArgs(ac, av);
	window.windowCreateDevice();
	if (window.getDevice() == nullptr)
		return 1;

	window.initDrivers();
	window.initLoader();
	window.initCamera();
	window.initEventReceiver();
	window.initChessBoard();

	std::cout << " -------------- LINKING CLIENT AND ZAPPY -------------- "	<< std::endl;
	window.linkZappyGame(zappy);
	window.linkGuiClient(client);
	std::cout << " -------------- CREATING SOCKET -------------- "	<< std::endl;
	window.getGuiClient()->createSocket();
	std::cout << " -------------- INITIALIZING IDENTIFICATION -------------- "	<< std::endl;
	window.getGuiClient()->initIdentification();
	std::cout << " -------------- INITIALIZING SERVER DATA RECEIVER -------------- "	<< std::endl;
	std::cout << "map size is " << window.getGuiClient()->getMapSize() << std::endl;
	std::cout << "time unit is " << window.getGuiClient()->getTimeUnit() << std::endl;
	window.getGuiClient()->makeNonBlocking();
	std::cout << " -------------- INITIALIZING CHESS BOARD -------------- "	<< std::endl;
	window.getChessBoard()->createBoard();

	window.getLinkedZappyGame()->loadChessPieces();
	window.getLinkedZappyGame()->addPlayer("player1");
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setPos(5, 3);
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setZ(2);
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setOrientation(0, 0, 2);
	window.getLinkedZappyGame()->getPlayer("player1")->updatePlayerPos();
	window.getLinkedZappyGame()->getPlayer("player1")->setLevel(2);

	std::cout << " -------------- RUNNING WINDOW -------------- "	<< std::endl;
	window.runWindow();
	return 0;
}
