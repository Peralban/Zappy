/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#include "zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

int main(void)
{
	int width = 1920;
	int height = 1080;
	int platformX = 30;
	int platformY = 10;
	float tileSize = 15.0f;
	quality quality = MID;
	bool debug = false;

	std::cout << "Starting Zappy" << std::endl;

	ZappyGame zappy = ZappyGame();

	irrlichtWindow window(width, height, platformX, platformY, tileSize, irr::video::EDT_OPENGL, quality, debug);
	window.windowCreateDevice();
	if (window.getDevice() == nullptr)
		return 1;
	window.initDrivers();
	window.initCamera();
	window.initChessBoard();
	window.initEventReceiver();
	window.linkZappyGame(&zappy);
	zappy.loadChessPieces();
	window.getLinkedZappyGame()->addPlayer("player1");
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setPos(5, 3);
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setConvertedZ(5.0f);
	window.getLinkedZappyGame()->getPlayer("player1")->getPlayerPosition()->setOrientation(0, 0, 2);
	window.getLinkedZappyGame()->getPlayer("player1")->updatePlayerPos();
	window.getLinkedZappyGame()->getPlayer("player1")->setLevel(2);
	window.runWindow();
	return 0;
}