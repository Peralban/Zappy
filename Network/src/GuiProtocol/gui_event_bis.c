/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void pex(server_t *server, void *data)
{
    client_t *client = (client_t *)data;
    char buffer[1024];

    sprintf(buffer, "pex %d\n", client->drone->id);
    send_all_graphics(server, buffer);
}