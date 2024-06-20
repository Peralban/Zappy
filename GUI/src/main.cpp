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

	irrlichtWindow window(width, height, irr::video::EDT_OPENGL, quality, debug);
	window.parseArgs(ac, av);
	window.windowCreateDevice();
	if (window.getDevice() == nullptr)
		return 1;

	window.initDrivers();
	window.initLoader();
	window.initCamera();
	window.initEventReceiver();

	std::cout << " -------------- LINKING CLIENT AND ZAPPY -------------- "	<< std::endl;
	window.linkZappyGame(zappy);
	std::cout << " -------------- LINKING GUI CLIENT -------------- "	<< std::endl;
	window.linkGuiClient(client);
	std::cout << " -------------- SETTING PLATFORM SIZE -------------- "	<< std::endl;
	zappy->setPlatformSize(platformX, platformY);
	std::cout << " -------------- SETTING TILE SIZE -------------- "	<< std::endl;
	zappy->setTileSize(tileSize);
	std::cout << " -------------- CREATING SOCKET -------------- "	<< std::endl;
	window.getGuiClient()->createSocket();
	std::cout << " -------------- INITIALIZING IDENTIFICATION -------------- "	<< std::endl;
	window.getGuiClient()->askInitData();

	std::cout << " -------------- INITIALIZING CHESS BOARD -------------- "	<< std::endl;
	window.getGuiClient()->makeNonBlocking();

	window.getLinkedZappyGame()->loadChessPieces();
	window.getLinkedZappyGame()->addPlayer("player1");
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setPos(5, 3);
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setZ(2);
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setOrientation(0, 0, 2);
	window.getLinkedZappyGame()->getPlayer("player1")->updatePlayerPos();
	window.getLinkedZappyGame()->createTeam("team1", 255, 0, 0, 255);
	window.getLinkedZappyGame()->getPlayer("player1")->setTeamFromName("team1");
	window.getLinkedZappyGame()->getPlayer("player1")->setLevel(2);

	std::cout << " -------------- RUNNING WINDOW -------------- "	<< std::endl;
	window.runWindow();
	return 0;
}
