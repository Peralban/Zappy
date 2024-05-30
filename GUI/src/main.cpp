/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#include "main.hpp"

IrrlichtDevice *initWindow(int width, int height, int platformX, int platformY, float tileSize)
{
	video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(width, height), 16);
	if (device == 0)
		return nullptr;
	device->getCursorControl()->setVisible(false);

	return device;
}

void initElement(IVideoDriver *driver, ISceneManager *smgr, int platformX, int platformY, float tileSize)
{
	int height = (platformX + platformY) * 3 + 25;

	chessBoard(smgr, driver, platformX, platformY, tileSize);
	std::cout << "chessBoard created" << std::endl;
	smgr->addCameraSceneNodeFPS();
	// droite-gauche   haut-bas   avant-arriere
	smgr->getActiveCamera()->setPosition(core::vector3df(-15, height, -15));
	smgr->getActiveCamera()->setTarget(core::vector3df(50, 35, 50));
	smgr->getActiveCamera()->setFarValue(10000.0f);
	smgr->getActiveCamera()->setNearValue(0.1f);
	smgr->getActiveCamera()->setAspectRatio(1.33f);
	smgr->getActiveCamera()->setInputReceiverEnabled(true);
	smgr->getActiveCamera()->setDebugDataVisible(scene::EDS_FULL);
	smgr->getActiveCamera()->setViewMatrixAffector(core::matrix4());
}

int main(void)
{
	int width = 1920;
	int height = 1080;
	int platformX = 25;
	int platformY = 25;
	float tileSize = 10.0f;
	int lastFPS = -1;

	IrrlichtDevice *device = initWindow(width, height, platformX, platformY, tileSize);
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	myEventReceiver receiver(device);
	device->setEventReceiver(&receiver);

	initElement(driver, smgr, platformX, platformY, tileSize);

	while(device->run()) {
		if (device->isWindowActive()) {
        	driver->beginScene(true, true, video::SColor(255, 100, 101, 140));
			smgr->drawAll();
			driver->endScene();

		}
		else
			device->yield();
	}

	device->drop();
	return 0;
}