/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#include "zappyIrrlicht/irrlichtWindow.hpp"

int main(void)
{
	int width = 1920;
	int height = 1080;
	int platformX = 30;
	int platformY = 10;
	float tileSize = 10.0f;
	quality quality = MID;
	int lastFPS = -1;

	ZappyGame zappy = ZappyGame();

	irrlichtWindow window(width, height, platformX, platformY, tileSize, video::EDT_OPENGL);
	std::cout << "Creating window..." << std::endl;
	window.windowCreateDevice();
	if (window.getDevice() == nullptr)
		return 1;
	std::cout << "Window created\n"
	<< "Initializing drivers..." << std::endl;
	window.initDrivers();
	std::cout << "Drivers initialized\n"
	<< "Initializing camera..." << std::endl;
	window.initCamera();
	std::cout << "Camera initialized\n"
	<< "Initializing chess board..." << std::endl;
	window.initChessBoard();
	std::cout << "Chess board initialized\n"
	<< "Initializing event receiver..." << std::endl;
	window.initEventReceiver();
	std::cout << "Event receiver initialized\n"
	<< "Creating zappy game..." << std::endl;
	window.linkZappyGame(&zappy);
	std::cout << "Done creating zappy game\n"
	<< "Loading chess pieces..." << std::endl;
	zappy.loadChessPieces();
	std::cout << "Chess pieces loaded\n"
	<< "Creating a player..." << std::endl;
	window.getLinkedZappyGame()->addPlayer("player1");
	std::cout << "Player created\n"
	<< "Running window..." << std::endl;
	window.runWindow();
	std::cout << "stopping window" << std::endl;
	return 0;
}