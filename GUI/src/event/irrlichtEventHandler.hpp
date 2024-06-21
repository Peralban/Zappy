/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** eventHandler
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "../interface/AError.hpp"

/**
 * @class myEventReceiver
 * @brief The myEventReceiver class is responsible for handling events in the Irrlicht application.
 */
class myEventReceiver : public irr::IEventReceiver {
public:

    /**
     * @brief Constructs a myEventReceiver object.
     * @param device The pointer to the Irrlicht device.
     */
    myEventReceiver(irr::IrrlichtDevice* device);

    /**
     * @brief Destructs the myEventReceiver object.
     */
    ~myEventReceiver();

    /**
     * @brief Callback function that is called when an event occurs.
     * @param event The event that occurred.
     * @return True if the event was handled, false otherwise.
     */
    bool OnEvent(const irr::SEvent& event) override;

    /**
     * @brief Handles key press events.
     * @param event The key press event.
     * @return True if the key press event was handled, false otherwise.
     */
    bool keyPress(const irr::SEvent& event);

    class NullableDevice : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to create myEventReceiver but given device is null".
         */
        NullableDevice() : AError("Trying to create myEventReceiver but given device is null.") {}
    };

    class UnsetDevice : public AError {
    public:
        /**
         * @brief Display an error message.
         * @param message The error message to display. Defaults to "Trying to handle an event but device is not setted".
         */
        UnsetDevice() : AError("Trying to handle an event but device is not setted.") {}
    };

private:
    irr::IrrlichtDevice* _Device; /**< Pointer to the Irrlicht device. */
};
