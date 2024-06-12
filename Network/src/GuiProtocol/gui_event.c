/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void gui_event(event_type_e event, server_t *server, void *data)
{
    for (int i = 0; event_gui[i].event_type != 0; i++) {
        if (event_gui[i].event_type == event) {
            event_gui[i].function(server, data);
            return;
        }
    }
}