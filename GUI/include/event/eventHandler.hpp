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
    myEventReceiver(IrrlichtDevice* device) : Device(device) {
        std::cout << "Event Receiver created" << std::endl;
    }

    bool OnEvent(const SEvent& event) override {
        std::cout << "Event received" << std::endl;
        // Check if a key was pressed
        if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown) {
            // If the key pressed was 'ESC', close the device
            if (event.KeyInput.Key == KEY_ESCAPE) {
                Device->closeDevice();
                return true;
            }
        }
        return false;
    }
private:
    IrrlichtDevice* Device;
};
