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
	quality quality = LowPoly;
	int lastFPS = -1;

	irrlichtWindow window(width, height, platformX, platformY, tileSize, video::EDT_OPENGL);
	std::cout << "Creating window" << std::endl;
	window.windowCreateDevice();
	if (window.getDevice() == nullptr)
		return 1;
	std::cout << "Window created" << std::endl;
	std::cout << "Initializing drivers" << std::endl;
	window.initDrivers();
	std::cout << "Drivers initialized" << std::endl;
	std::cout << "Initializing camera" << std::endl;
	window.initCamera();
	std::cout << "Camera initialized" << std::endl;
	std::cout << "Initializing chess piece" << std::endl;
	window.initChessPiece();
	std::cout << "Chess piece initialized" << std::endl;
	std::cout << "Initializing chess board" << std::endl;
	window.initChessBoard();
	std::cout << "Chess board initialized" << std::endl;
	std::cout << "Initializing event receiver" << std::endl;
	window.initEventReceiver();
	std::cout << "Event receiver initialized" << std::endl;
	std::cout << "Running window" << std::endl;
	window.runWindow();
	std::cout << "stopping window" << std::endl;

	return 0;
}