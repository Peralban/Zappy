/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#include "irrlichtEventHandler.hpp"
#include <iostream>

myEventReceiver::myEventReceiver(irr::IrrlichtDevice* device) :
    _Device(device)
{
}

myEventReceiver::~myEventReceiver()
{
}

bool myEventReceiver::OnEvent(const irr::SEvent& event) {
    if (event.EventType != irr::EET_KEY_INPUT_EVENT)
        return false;
    if (event.KeyInput.PressedDown)
        return keyPress(event);
    return false;
}

bool myEventReceiver::keyPress(const irr::SEvent& event)
{
    irr::EKEY_CODE keyCode = event.KeyInput.Key;

    if (keyCode == irr::KEY_ESCAPE) {
        _Device->closeDevice();
        return true;
    }
    if (keyCode == irr::KEY_KEY_P) {
        const irr::core::vector3df& position = _Device->getSceneManager()->getActiveCamera()->getPosition();
        const irr::core::vector3df& target = _Device->getSceneManager()->getActiveCamera()->getTarget();
        std::cout << "Position: (" << position.X << ", " << position.Y << ", " << position.Z << ")" << std::endl;
        std::cout << "Target: (" << target.X << ", " << target.Y << ", " << target.Z << ")" << std::endl;
        return false;
    }
    return false;
}