/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#pragma once

#include <irrlicht/irrlicht.h>

class myEventReceiver : public irr::IEventReceiver {
public:
    myEventReceiver(irr::IrrlichtDevice* device);
    ~myEventReceiver();

    bool OnEvent(const irr::SEvent& event) override;
    bool keyPress(const irr::SEvent& event);

private:
    irr::IrrlichtDevice* _Device;
};
