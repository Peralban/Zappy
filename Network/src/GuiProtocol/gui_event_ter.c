/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void pfk(server_t *server, void *data)
{
    drone_t *drone = (drone_t *)data;
    char buffer[1024] = {0};

    sprintf(buffer, "pfk %d\n", drone->id);
    send_all_graphics(server, buffer);
}
