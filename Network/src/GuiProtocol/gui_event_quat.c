/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void gui_enw(server_t *server, drone_t *drone, egg_t *egg)
{
    char buffer[1024] = {0};

    sprintf(buffer, "enw %d %d %d %d\n", egg->id, drone->id,
        drone->x, drone->y);
    send_all_graphics(server, buffer);
}

void gui_ebo(server_t *server, egg_t *egg)
{
    char buffer[1024] = {0};

    sprintf(buffer, "ebo %d\n", egg->id);
    send_all_graphics(server, buffer);
}

void gui_edi(server_t *server, egg_t *egg)
{
    char buffer[1024] = {0};

    sprintf(buffer, "edi %d\n", egg->id);
    send_all_graphics(server, buffer);
}
