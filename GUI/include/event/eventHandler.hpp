/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#pragma once

#include "main.hpp"

class myEventReceiver : public IEventReceiver {
public:
    myEventReceiver(IrrlichtDevice* device);
    ~myEventReceiver();
    bool OnEvent(const SEvent& event) override;
    void keyPress(const SEvent& event);
private:
    IrrlichtDevice* Device;
};
