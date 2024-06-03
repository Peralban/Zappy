/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#include "event/eventHandler.hpp"

myEventReceiver::myEventReceiver(IrrlichtDevice* device) :
    _Device(device)
{
}

myEventReceiver::~myEventReceiver()
{
}

bool myEventReceiver::OnEvent(const SEvent& event) {
    if (event.EventType != EET_KEY_INPUT_EVENT)
        return false;
    if (event.KeyInput.PressedDown)
        return keyPress(event);
    return false;
}

bool myEventReceiver::keyPress(const SEvent& event)
{
    irr::EKEY_CODE keyCode = event.KeyInput.Key;

    if (keyCode == KEY_ESCAPE) {
        _Device->closeDevice();
        return true;
    }
    if (keyCode == KEY_KEY_P) {
        const core::vector3df& position = _Device->getSceneManager()->getActiveCamera()->getPosition();
        const core::vector3df& target = _Device->getSceneManager()->getActiveCamera()->getTarget();
        std::cout << "Position: (" << position.X << ", " << position.Y << ", " << position.Z << ")" << std::endl;
        std::cout << "Target: (" << target.X << ", " << target.Y << ", " << target.Z << ")" << std::endl;
        return false;
    }
    return false;
}